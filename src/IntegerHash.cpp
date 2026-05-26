#include "simple_integer_hash/IntegerHash.hpp"

namespace simple_integer_hash {
namespace {

// FNV-1a 64-bit constants.
constexpr std::uint64_t kFnvOffsetBasis = 14695981039346656037ull;
constexpr std::uint64_t kFnvPrime = 1099511628211ull;

// MurmurHash3 finalizer (fmix64) - provides good avalanche properties.
constexpr std::uint64_t fmix64(std::uint64_t k) noexcept {
  k ^= k >> 33;
  k *= 0xff51afd7ed558ccdull;
  k ^= k >> 33;
  k *= 0xc4ceb9fe1a85ec53ull;
  k ^= k >> 33;
  return k;
}

constexpr std::uint64_t fnv1a_64(const std::string& s) noexcept {
  std::uint64_t h = kFnvOffsetBasis;
  for (unsigned char c : s) {
    h ^= static_cast<std::uint64_t>(c);
    h *= kFnvPrime;
  }
  return h;
}

} // namespace

IntegerHash::IntegerHash(std::string value)
    : value_(std::move(value)), hash_(compute_hash(value_)) {}

bool IntegerHash::equals(const std::string& other) const noexcept {
  return value_ == other;
}

std::uint64_t IntegerHash::hash() const noexcept { return hash_; }

const std::string& IntegerHash::str() const noexcept { return value_; }

std::uint64_t IntegerHash::compute_hash(const std::string& value) noexcept {
  // Not cryptographic; intended for teaching / hash tables.
  return fmix64(fnv1a_64(value));
}

} // namespace simple_integer_hash


