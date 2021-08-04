project(gmpp)
cmake_minimum_required(VERSION 3.16)

add_library(
    gmpp
    STATIC
    src/Integer.cxx
)

target_include_directories(
    gmpp
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(
    gmpp
    PUBLIC
    cxx_std_17
)

target_link_libraries(
    gmpp
    PUBLIC
    gmp
)

add_subdirectory(tests)