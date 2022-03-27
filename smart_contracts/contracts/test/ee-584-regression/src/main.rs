#![no_std]
#![no_main]

extern crate alloc;

use alloc::string::String;

use dimension_contract::contract_api::{runtime, storage};
use dimension_types::ApiError;

#[no_mangle]
pub extern "C" fn call() {
    let _ = storage::new_uref(String::from("Hello, World!"));
    runtime::revert(ApiError::User(999))
}
