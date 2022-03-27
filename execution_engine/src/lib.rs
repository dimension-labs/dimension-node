//! The engine which executes smart contracts on the Dimension network.

#![doc(html_root_url = "https://docs.rs/dimension-execution-engine/1.4.4")]
#![doc(
    html_favicon_url = "https://raw.githubusercontent.com/DimensionLabs/dimension-node/master/images/DimensionLabs_Logo_Favicon_RGB_50px.png",
    html_logo_url = "https://raw.githubusercontent.com/DimensionLabs/dimension-node/master/images/DimensionLabs_Logo_Symbol_RGB.png",
    test(attr(forbid(warnings)))
)]
#![warn(
    missing_docs,
    trivial_casts,
    trivial_numeric_casts,
    unused_qualifications
)]

pub mod config;
pub mod core;
pub mod shared;
/// Storage for the execution engine.
pub mod storage;
