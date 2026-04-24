cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DUNICODE -D_UNICODE)

project(inheritance_chess_project VERSION 1.0.0 LANGUAGES CXX)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add subdirectories for each component
add_subdirectory(cci)
add_subdirectory(cpl)
add_subdirectory(cbm)
add_subdirectory(ctu)
add_subdirectory(ces)
add_subdirectory(cgh)
add_subdirectory(cei)

# Main executable
add_executable(${EXE_NAME} main.cpp)

# Link main executable with all component libraries
target_link_libraries(${EXE_NAME}
    cci
    cpl
    cbm
    ctu
    ces
    cgh
    cei
)

# Add tests
add_subdirectory(tests)
