include(${CMAKE_SCRIPTS_DIR}/googletest.cmake)

add_executable(
  window-starter-test
  test_main.cpp
)

target_link_libraries(
  window-starter-test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(window-starter-test)
