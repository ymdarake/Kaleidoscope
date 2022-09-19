cmake_minimum_required (VERSION 3.8)

project(Kaleidoscope CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(Kaleidoscope src/main.cpp)


## Test

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/1336c4b6d1a6f4bc6beebccb920e5ff858889292.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --coverage") # 追加
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # 追加


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME}-googletest src/foo.cpp test/test_foo.cpp)
target_link_libraries(${PROJECT_NAME}-googletest gtest_main)
target_include_directories(${PROJECT_NAME}-googletest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_test(NAME test COMMAND ${PROJECT_NAME}-googletest)
enable_testing()
