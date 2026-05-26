add_executable(simple_integer_hash_example
  hash_example.cpp
)

target_link_libraries(simple_integer_hash_example
  PRIVATE
    SimpleIntegerHash::simple_integer_hash
)

target_compile_features(simple_integer_hash_example PRIVATE cxx_std_17)

