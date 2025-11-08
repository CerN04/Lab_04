cmake_minimum_required(VERSION 3.10)
project(Lab_04)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git  
  GIT_TAG v1.15.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(main main.cpp)
target_include_directories(main PUBLIC include)


enable_testing()
add_executable(tests tests/test.cpp)
target_link_libraries(tests GTest::gtest)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME MyProjectTests COMMAND tests)