#![no_std]
#![no_main]

extern crate alloc;

use alloc::vec::Vec;

use dimension_contract::{
    contract_api::{runtime, system},
    unwrap_or_revert::UnwrapOrRevert,
};
use dimension_types::{account::AccountHash, ApiError, U512};

const ARG_ACCOUNTS: &str = "accounts";
const ARG_SEED_AMOUNT: &str = "seed_amount";

#[no_mangle]
pub extern "C" fn call() {
    let accounts: Vec<AccountHash> = runtime::get_named_arg(ARG_ACCOUNTS);
    let seed_amount: U512 = runtime::get_named_arg(ARG_SEED_AMOUNT);
    for account_hash in accounts {
        system::transfer_to_account(account_hash, seed_amount, None)
            .unwrap_or_revert_with(ApiError::Transfer);
    }
}
