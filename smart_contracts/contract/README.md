# `dimension-contract`

[![LOGO](https://raw.githubusercontent.com/dimension-labs/dimension-node/master/images/dimension-association-logo-primary.svg)](https://dimension.network/)

[![Crates.io](https://img.shields.io/crates/v/dimension-contract)](https://crates.io/crates/dimension-contract)
[![Documentation](https://docs.rs/dimension-contract/badge.svg)](https://docs.rs/dimension-contract)
[![License](https://img.shields.io/badge/license-Apache-blue)](https://github.com/DimensionLabs/dimension-node/blob/master/LICENSE)

A library for developing Dimension network smart contracts.

## no_std

The crate is `no_std`, but uses the `core` and `alloc` crates.  It is recommended to build Wasm smart contracts in a
`no_std` environment as this generally yields smaller, and hence cheaper, binaries.

## Compile-time features

### `no-std-helpers`

Enabled by default.

Given that the library is intended to be consumed by smart-contract binaries, and that in a `no_std` environment these
will all require to provide an [alloc error handler](https://github.com/rust-lang/rust/issues/51540) and an
[eh_personality](https://doc.rust-lang.org/unstable-book/language-features/lang-items.html#more-about-the-language-items),
then this crate provides these when `no-std-helpers` is enabled.  This unfortunately requires the use of nightly Rust.

For further convenience, enabling this feature also provides a global allocator suitable for use in a `no_std`
environment.

If you wish to use a different global allocator, or provide different panic/out-of-memory handlers, then add the
following to your Cargo.toml:

```toml
dimension-contract = { version = "1", default-features = false }
```

### `test-support`

Disabled by default.

To help support smart contract debugging, enabling the `test-support` feature makes the function
`contract_api::runtime::print(text: &str)` available.  If the contract is being tested offchain using the
`dimension-engine-test-support` crate, then the contract can output text to the console for debugging.

```toml
dimension-contract = { version = "1", features = ["test-support"] }
```

## License

Licensed under the [Apache License Version 2.0](https://github.com/dimension-labs/dimension-node/blob/master/LICENSE).
