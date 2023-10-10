cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(codegen)

# we require Python for this recipe to work
find_package(Python3 QUIET REQUIRED)

# generate directory where we place the generated code
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)

# upper bound
set(MAX_NUMBER "100" CACHE STRING "Upper bound for primes")

# generate code
add_custom_command(
        OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/generated/primes.hpp
        COMMAND
        ${Python3_EXECUTABLE} generate.py ${MAX_NUMBER} ${CMAKE_CURRENT_BINARY_DIR}/generated/primes.hpp
        WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS
        generate.py
)

add_executable(example "")

target_sources(example
        PRIVATE
        example.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/generated/primes.hpp
)

target_include_directories(example
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)