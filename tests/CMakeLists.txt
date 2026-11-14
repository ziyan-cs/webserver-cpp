function(add_project_test name source library)
  add_executable(${name} ${source})
  target_link_libraries(${name} PRIVATE ${library})
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
  )
  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_project_test(config_test config_test.cpp base)
add_project_test(logger_test logger_test.cpp base)
add_project_test(core_test core_test.cpp core)
