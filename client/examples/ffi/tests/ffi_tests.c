#include "unity.h"
#include "dimension_client.h"

void setUp(void) {
    dimension_setup_client();
}

void tearDown(void) {
    dimension_shutdown_client();
}

void test_should_be_no_last_error_on_startup(void) {
    unsigned char error[255] = {0};
    int bytes_read = dimension_get_last_error(error, 255);
    TEST_ASSERT_EQUAL_INT(0, bytes_read);
}

void test_should_get_last_error_after_bad_request(void) {
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
    session_params.session_name = "standard_payment";
    session_params.session_entry_point = "session_entry_point";

    unsigned char response_buffer[1024] = {0};

    dimension_error_t success =
        dimension_put_deploy("1", "", false, &deploy_params, &session_params,
                          &payment_params, response_buffer, 1024);

    TEST_ASSERT_NOT_EQUAL_INT(DIMENSION_SUCCESS, success);

    unsigned char error[255] = {0};
    int bytes_read = dimension_get_last_error(error, 255);
    TEST_ASSERT_EQUAL_STRING("Failed to get RPC response: builder error: relative URL without a base",
                             error);
}

void test_keygen_should_work_with_valid_algorithm(void) {
    dimension_error_t success =
        dimension_keygen("./dimension_keygen_test", "ed25519", false);

    TEST_ASSERT_EQUAL_INT(DIMENSION_SUCCESS, success);
}

void test_keygen_should_fail_with_invalid_algorithm(void) {
    dimension_error_t success =
        dimension_keygen("./dimension_keygen_test", "lolwut", false);

    TEST_ASSERT_NOT_EQUAL_INT(DIMENSION_SUCCESS, success);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_should_be_no_last_error_on_startup);
    RUN_TEST(test_should_get_last_error_after_bad_request);
    RUN_TEST(test_keygen_should_work_with_valid_algorithm);
    RUN_TEST(test_keygen_should_fail_with_invalid_algorithm);
    return UNITY_END();
}
