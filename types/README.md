# `dimension-types`

[![LOGO](https://raw.githubusercontent.com/dimension-labs/dimension-node/master/images/dimension-association-logo-primary.svg)](https://dimension.network/)

[![Build Status](https://drone-auto-dimension-labs.dimensionlabs.io/api/badges/dimension-labs/dimension-node/status.svg?branch=dev)](http://drone-auto-dimension-labs.dimensionlabs.io/dimension-labs/dimension-node)
[![Crates.io](https://img.shields.io/crates/v/dimension-types)](https://crates.io/crates/dimension-types)
[![Documentation](https://docs.rs/dimension-types/badge.svg)](https://docs.rs/dimension-types)
[![License](https://img.shields.io/badge/license-Apache-blue)](https://github.com/DimensionLabs/dimension-node/blob/master/LICENSE)

Types shared by many dimension crates for use on the Dimension network.

## `no_std`

The crate is `no_std` (using the `core` and `alloc` crates) unless any of the following features are enabled:

* `json-schema` to enable many types to be used to produce JSON-schema data via the [`schemars`](https://crates.io/crates/schemars) crate
* `datasize` to enable many types to derive the [`DataSize`](https://github.com/dimensionlabs/datasize-rs) trait
* `gens` to enable many types to be produced in accordance with [`proptest`](https://crates.io/crates/proptest) usage for consumption within dependee crates' property testing suites

## License

Licensed under the [Apache License Version 2.0](https://github.com/dimension-labs/dimension-node/blob/master/LICENSE).
