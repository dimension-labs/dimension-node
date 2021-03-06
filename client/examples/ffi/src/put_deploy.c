#include <stdio.h>

#include "dimension_client.h"

#define RESPONSE_BUFFER_LEN 1024
#define ERROR_LEN 255
#define NODE_ADDRESS "http://localhost:50101"
#define RPC_ID "1"
#define VERBOSE 0

int main(int argc, char **argv) {
    dimension_setup_client();

    dimension_deploy_params_t deploy_params = {0};
    deploy_params.secret_key = "resources/local/secret_keys/node-1.pem";
    deploy_params.ttl = "10s";
    deploy_params.chain_name = "dimension-charlie-testnet1";
    deploy_params.gas_price = "11";

    dimension_payment_params_t payment_params = {0};
    payment_params.payment_amount = "1000";

    const char *payment_args[2] = {
        "name_01:bool='false'",
        "name_02:i32='42'",
    };
    payment_params.payment_args_simple = (const char *const *)&payment_args;
    payment_params.payment_args_simple_len = 2;

    dimension_session_params_t session_params = {0};

    unsigned char response_buffer[RESPONSE_BUFFER_LEN] = {0};
    dimension_error_t success = dimension_put_deploy(
        RPC_ID, NODE_ADDRESS, VERBOSE, &deploy_params, &session_params,
        &payment_params, response_buffer, RESPONSE_BUFFER_LEN);
    if (success == DIMENSION_SUCCESS) {
        printf("Got successful response\n%s\n", response_buffer);
    } else {
        unsigned char error[ERROR_LEN] = {0};
        dimension_get_last_error(error, ERROR_LEN);
        printf("Got error:\n%s\n", error);
    }
    printf("Done.\n");

    dimension_shutdown_client();

    return 0;
}
