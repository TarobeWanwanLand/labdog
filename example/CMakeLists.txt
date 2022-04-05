set(EXAMPLE_NAME "example")

add_executable(${EXAMPLE_NAME}
    bar.cpp
)

target_link_libraries(${EXAMPLE_NAME} PRIVATE labdog::labdog)

# Set C++ version
set_target_properties(${EXAMPLE_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

install(
  TARGETS ${EXAMPLE_NAME}
  RUNTIME DESTINATION bin
)
