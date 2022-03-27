#!/usr/bin/env bash
#
#######################################
# Compiles node software.
# Globals:
#   NCTL - path to nctl home directory.
#   NCTL_DIMENSION_HOME - path to dimension node repo.
#   NCTL_COMPILE_TARGET - flag indicating whether software compilation target is release | debug.
########################################

source "$NCTL"/sh/utils/main.sh

pushd "$NCTL_DIMENSION_HOME" || exit

if [ "$NCTL_COMPILE_TARGET" = "debug" ]; then
    cargo build --package dimension-node --features dimension-mainnet
else
    cargo build --release --package dimension-node --features dimension-mainnet
fi

popd || exit
