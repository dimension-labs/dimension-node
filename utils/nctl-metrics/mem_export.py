#!/usr/bin/env python

#: A small script that makes memory usage of nctl nodes available to prometheus.

# Requirements: `prometheus_client`, `psutil`

from http.client import HTTPConnection
import os
import socket
import sys
import time
from xmlrpc import client

from prometheus_client import start_http_server, Summary, Gauge
import psutil


class UnixStreamHTTPConnection(HTTPConnection):
    def connect(self):
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.sock.connect(self.host)


class UnixStreamTransport(client.Transport, object):
    def __init__(self, socket_path):
        self.socket_path = socket_path
        super(UnixStreamTransport, self).__init__()

    def make_connection(self, host):
        return UnixStreamHTTPConnection(self.socket_path)


def main():
    net_name = "net-1"

    # Workaround letting us use symlink paths to shorten socket names. Otherwise symlinks will be
    # resolved by Python's cwd functions (which call libc internally) to resolve `.`.
    cwd = os.popen("pwd -L").read().strip()

    sock_addr = os.path.abspath(
        os.path.join(
            cwd,
            "..",
            "nctl",
            "assets",
            net_name,
            "daemon",
            "socket",
            "supervisord.sock",
        )
    )
    delay = 1

    gauges = {
        "rss": Gauge("os_mem_rss_bytes", "Resident Set Size", ["node"]),
        "vms": Gauge("os_mem_vms_bytes", "Virtual Memory Size", ["node"]),
        "shared": Gauge("os_mem_shared_bytes", "Shared memory size", ["node"]),
        "text": Gauge("os_mem_text_bytes", "Text memory size", ["node"]),
        "lib": Gauge("os_mem_lib_bytes", "Lib memory size", ["node"]),
        "data": Gauge("os_mem_data_bytes", "Data memory size", ["node"]),
        "dirty": Gauge("os_mem_dirty_bytes", "Dirty memory size", ["node"]),
    }

    start_http_server(8000)

    while True:
        print("Retrieving data for from {}".format(sock_addr))

        try:
            proxy = client.ServerProxy(
                "http://localhost", transport=UnixStreamTransport(sock_addr)
            )

            all_proc_info = proxy.supervisor.getAllProcessInfo()

            for info in all_proc_info:
                name = info["name"]

                # Only interested in dimension nodes.
                if not name.startswith("dimension-net"):
                    continue

                # PID 0 means the process is not running.
                pid = info["pid"]
                if pid == 0:
                    continue

                try:
                    proc = psutil.Process(info["pid"])
                    mem_info = proc.memory_info()
                    print("{}: {}".format(name, mem_info))

                    for key in gauges.keys():
                        gauges[key].labels(node=name).set(getattr(mem_info, key))
                except Exception as e:
                    print("failed to get process info for {}: {}".format(name, e))
        except Exception as e:
            print("failed: {}".format(e))

        time.sleep(delay)


if __name__ == "__main__":
    main()
