file(GLOB TEST_SOURCES "./test_*.cpp")

add_executable(test_${EXE_NAME} ${TEST_SOURCES})

target_link_libraries(test_${EXE_NAME} 
    gtest
    gtest_main
    gmock
    gmock_main
)

target_include_directories(test_${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
file(GLOB PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
target_sources(test_${EXE_NAME} PRIVATE ${PROJECT_SOURCES})

add_test(NAME "${EXE_NAME}_Tests" COMMAND test_${EXE_NAME})

enable_testing()
