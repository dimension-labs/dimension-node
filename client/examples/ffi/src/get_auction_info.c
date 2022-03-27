#include <stdio.h>

#include "dimension_client.h"

#define RESPONSE_BUFFER_LEN 1048576
#define ERROR_LEN 255
#define NODE_ADDRESS "http://localhost:50101"
#define RPC_ID "1"
#define BLOCK_ID ""
#define VERBOSE 0

int main(int argc, char **argv) {
    dimension_setup_client();

    unsigned char response_buffer[RESPONSE_BUFFER_LEN] = {0};
    dimension_error_t success = dimension_get_auction_info(
        RPC_ID, NODE_ADDRESS, VERBOSE, BLOCK_ID, response_buffer, RESPONSE_BUFFER_LEN);
    if (success == DIMENSION_SUCCESS) {
        printf("Got successful response:\n%s\n", response_buffer);
    } else {
        unsigned char error[ERROR_LEN] = {0};
        dimension_get_last_error(error, ERROR_LEN);
        printf("Got error:\n%s\n", error);
    }
    printf("Done.\n");

    dimension_shutdown_client();

    return 0;
}
