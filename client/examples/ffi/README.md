# dimension_client FFI examples

It's possible to use the `dimension_client` library from C:


## Building with CMake

To build the examples, from the root of `dimension-node` run:

```
cmake -Hclient/examples/ffi -Btarget/build -DCMAKE_BUILD_TYPE=Debug
cmake --build target/build
```

In the `target/build` directory which was created, you should see the binaries for the examples that have been compiled.

The build also produces a shared library in `target/build/installed/lib/libdimension_client.so` and its header file in
`target/build/installed/include/dimension_client.h`.

```
#include "dimension_client.h
```


## Initial setup

Some resources need to be initialized before library functions can be called:

```
/* initialize dimension-client library */
dimension_setup_client();
```

After this, it's possible to call library functions to query the node.

For example:

```
unsigned char response_buffer[RESPONSE_BUFFER_LEN] = {0};
dimension_error_t response_code = dimension_get_auction_info(
    RPC_ID, NODE_ADDRESS, VERBOSE, response_buffer, RESPONSE_BUFFER_LEN);
if (response_code == DIMENSION_SUCCESS) {
    printf("get_auction_info: got successful response\n%s\n", response_buffer);
} else {
    /* handle error... see Error Handling below */
}
```


## Error handling

Errors are returned from the various library functions as `dimension_error_t`, but more detail can be gathered using
`get_last_error`, which will pull the last error that occurred in the library as a string.

```
if (response == DIMENSION_IO_ERROR) {
    /* first, initialize a buffer to hold our error string */
    unsigned char error[ERROR_LEN] = {0};

    /* ask for the description of the latest error, which was a DIMENSION_IO_ERROR in this case */
    dimension_get_last_error(error, ERROR_LEN);

    printf("got an IO error:\n%s\n", error);
}
```

Refer to `<project_root>/client/headers/dimension_client.h` as well as the examples in the `src` directory for more
information about specific functions and their arguments.


## Cleanup

In order to clean up and free any resources that the library has allocated, run:

```
/* finally, clean up after ourselves */
dimension_shutdown_client();
```
