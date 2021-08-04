add_executable(
    tests
    main.cxx
    tests_integer_operations.cxx
)

target_link_libraries(
    tests
    PRIVATE
    gmpp
)
