cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DUNICODE -D_UNICODE)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/build_gtest")
FetchContent_Declare( googletest
                      URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
                      EXCLUDE_FROM_ALL )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(inheritance_chess_project)

include_directories("include")
file(GLOB SOURCES "src/*.cpp")
add_executable(${EXE_NAME})
target_sources(${EXE_NAME} PRIVATE ${SOURCES} main.cpp)

enable_testing()
target_link_libraries(${EXE_NAME} GTest::gtest GTest::gtest_main)
add_subdirectory(tests)
