#ifndef SIMPLE_INTEGER_HASH_INTEGER_HASH_HPP
#define SIMPLE_INTEGER_HASH_INTEGER_HASH_HPP

#include <cstdint>
#include <string>

namespace simple_integer_hash {

class IntegerHash {
public:
  // Constructs from a string.
  explicit IntegerHash(std::string value);

  // Perfect equality (byte-for-byte) of the underlying string.
  bool equals(const std::string& other) const noexcept;

  // Returns the cached 64-bit hash of the string.
  std::uint64_t hash() const noexcept;

  // Expose the original string (useful for teaching/debugging).
  const std::string& str() const noexcept;

private:
  static std::uint64_t compute_hash(const std::string& value) noexcept;

  std::string value_;
  std::uint64_t hash_{};
};

} // namespace simple_integer_hash

#endif // SIMPLE_INTEGER_HASH_INTEGER_HASH_HPP


