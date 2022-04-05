set(EXAMPLE_NAME "example")

add_executable(${EXAMPLE_NAME}
    bar.cpp
)

target_link_libraries(${EXAMPLE_NAME} PRIVATE labdog::labdog)

install(
  TARGETS ${EXAMPLE_NAME}
  RUNTIME DESTINATION bin
)
