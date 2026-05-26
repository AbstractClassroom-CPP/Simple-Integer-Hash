cmake_minimum_required(VERSION 3.21)

project(SimpleIntegerHash
  VERSION 1.0.0
  DESCRIPTION "Simple string-to-uint64 integer hash (teaching repo)"
  LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest) # provides BUILD_TESTING option

if(PROJECT_IS_TOP_LEVEL)
  set(_sih_default_tests ON)
  set(_sih_default_example ON)
else()
  set(_sih_default_tests OFF)
  set(_sih_default_example OFF)
endif()

option(SIMPLE_INTEGER_HASH_BUILD_TESTING "Build the unit tests" ${_sih_default_tests})
option(SIMPLE_INTEGER_HASH_BUILD_EXAMPLE "Build the example executable" ${_sih_default_example})

add_library(simple_integer_hash
  src/IntegerHash.cpp
)
add_library(SimpleIntegerHash::simple_integer_hash ALIAS simple_integer_hash)

target_compile_features(simple_integer_hash PUBLIC cxx_std_17)

target_include_directories(simple_integer_hash
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_options(simple_integer_hash
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

set_target_properties(simple_integer_hash PROPERTIES
  EXPORT_NAME simple_integer_hash
  OUTPUT_NAME simple_integer_hash
)

# --- Installation / packaging (so this project can be used via find_package) ---
install(
  TARGETS simple_integer_hash
  EXPORT SimpleIntegerHashTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(SIMPLE_INTEGER_HASH_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/SimpleIntegerHash")

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/SimpleIntegerHashConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SimpleIntegerHashConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SimpleIntegerHashConfig.cmake"
  INSTALL_DESTINATION ${SIMPLE_INTEGER_HASH_INSTALL_CMAKEDIR}
)

install(
  EXPORT SimpleIntegerHashTargets
  FILE SimpleIntegerHashTargets.cmake
  NAMESPACE SimpleIntegerHash::
  DESTINATION ${SIMPLE_INTEGER_HASH_INSTALL_CMAKEDIR}
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/SimpleIntegerHashConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/SimpleIntegerHashConfigVersion.cmake"
  DESTINATION ${SIMPLE_INTEGER_HASH_INSTALL_CMAKEDIR}
)

# --- Subdirectories ---
if(SIMPLE_INTEGER_HASH_BUILD_TESTING AND BUILD_TESTING)
  add_subdirectory(testing)
endif()

if(SIMPLE_INTEGER_HASH_BUILD_EXAMPLE)
  add_subdirectory(example)
endif()


