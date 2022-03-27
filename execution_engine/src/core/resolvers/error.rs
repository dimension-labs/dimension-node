//! Errors that may be emitted by a host function resolver.
use thiserror::Error;

use dimension_types::ProtocolVersion;

/// Error conditions of a host function resolver.
#[derive(Error, Debug, Copy, Clone)]
pub enum ResolverError {
    /// Unknown protocol version.
    #[error("Unknown protocol version: {}", _0)]
    UnknownProtocolVersion(ProtocolVersion),
    /// WASM module does not export a memory section.
    #[error("No imported memory")]
    NoImportedMemory,
}
