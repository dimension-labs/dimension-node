#![no_std]
#![no_main]

use dimension_contract::{
    contract_api::{account, runtime},
    unwrap_or_revert::UnwrapOrRevert,
};
use dimension_types::{account::AccountHash, ApiError};

const ARG_ACCOUNT: &str = "account";

#[no_mangle]
pub extern "C" fn call() {
    let account: AccountHash = runtime::get_named_arg(ARG_ACCOUNT);
    account::remove_associated_key(account).unwrap_or_revert_with(ApiError::User(0))
}
