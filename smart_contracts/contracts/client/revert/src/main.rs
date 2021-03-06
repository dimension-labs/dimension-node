#![no_std]
#![no_main]

use dimension_contract::contract_api::runtime;
use dimension_types::ApiError;

#[no_mangle]
pub extern "C" fn call() {
    runtime::revert(ApiError::User(100))
}
