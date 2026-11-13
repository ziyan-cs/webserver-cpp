add_executable(config_test config_test.cpp)
target_link_libraries(config_test PRIVATE base)

add_test(NAME config_test COMMAND config_test)

add_executable(logger_test logger_test.cpp)
target_link_libraries(logger_test PRIVATE base)
add_test(NAME logger_test COMMAND logger_test)

set_target_properties(config_test logger_test PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
)
