## @file    configure_and_build.cmake
## @brief   Configure and build the project without running tests/executables.
## @details Decoupled build stage for local use and CI.

cmake_minimum_required(VERSION 3.28)

set(CMAKE_BUILD_TYPE "Release")
set(EXE_NAME "ichess_runner")
set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
set(BUILD_DIR "${ROOT_DIR}/build")
option(CLEAN_BUILD "Remove build directory before configuring" ON)
option(BUILD_TESTS "Build centralized tests target during configure/build" ON)

if(CLEAN_BUILD AND EXISTS "${BUILD_DIR}")
    message(STATUS "Cleaning: Removing old build directory...")
    file(REMOVE_RECURSE "${BUILD_DIR}")
endif()

# Also clear FetchContent test sub-build cache to avoid generator/platform mismatches
# when switching toolchains or generators between runs.
if(CLEAN_BUILD AND EXISTS "${ROOT_DIR}/tests/build_gtest")
    message(STATUS "Cleaning: Removing tests/build_gtest cache directory...")
    file(REMOVE_RECURSE "${ROOT_DIR}/tests/build_gtest")
endif()

file(MAKE_DIRECTORY "${BUILD_DIR}")

include(${CMAKE_CURRENT_LIST_DIR}/detect_generator.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/nmake_env_helpers.cmake)

message(STATUS "Build Type:    ${CMAKE_BUILD_TYPE}")
message(STATUS "Build Dir:     ${BUILD_DIR}")
message(STATUS "Executable:    ${EXE_NAME}")
message("")
message("======= CMake Configuration Phase =============================================")

set(CONFIG_COMMAND
    ${CMAKE_COMMAND}
    -S ${ROOT_DIR}
    -B ${BUILD_DIR}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DEXE_NAME=${EXE_NAME}
    -DENABLE_TESTS=${BUILD_TESTS}
)
if(NOT "${GENERATOR}" STREQUAL "")
    list(APPEND CONFIG_COMMAND -G "${GENERATOR}")
endif()
if(PLATFORM)
    list(APPEND CONFIG_COMMAND ${PLATFORM})
endif()

# Avoid inheriting machine-local vcpkg integration from developer environments.
set(_PREV_VCPKG_LOCALAPPDATA_DISABLED "$ENV{VCPkgLocalAppDataDisabled}")
set(ENV{VCPkgLocalAppDataDisabled} 1)

set(_USE_VSDEVCMD_WRAPPER OFF)
set(_CONFIG_WRAPPER "")
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows"
   AND GENERATOR STREQUAL "NMake Makefiles"
   AND DEFINED VS_DEVCMD
   AND EXISTS "${VS_DEVCMD}")
    set(_USE_VSDEVCMD_WRAPPER ON)
    set(_CONFIG_WRAPPER "${BUILD_DIR}/nmake_configure.cmd")
    create_vsdevcmd_wrapper_from_list("${_CONFIG_WRAPPER}" CONFIG_COMMAND)
endif()

run_with_optional_vsdevcmd_wrapper(
    ${_USE_VSDEVCMD_WRAPPER}
    "${_CONFIG_WRAPPER}"
    CONFIG_COMMAND
    "${ROOT_DIR}"
    CONFIG_RESULT
    CONFIG_OUTPUT
    CONFIG_ERROR
)

if(_PREV_VCPKG_LOCALAPPDATA_DISABLED STREQUAL "")
    unset(ENV{VCPkgLocalAppDataDisabled})
else()
    set(ENV{VCPkgLocalAppDataDisabled} "${_PREV_VCPKG_LOCALAPPDATA_DISABLED}")
endif()

if(NOT CONFIG_RESULT EQUAL 0)
    message(FATAL_ERROR "CMAKE CONFIGURATION FAILED\n${CONFIG_OUTPUT}\n${CONFIG_ERROR}")
endif()
message(STATUS "Configuration completed successfully")

message("")
message("======= CMake Parallel Build Phase ============================================")

if(NOT NUM_CORES GREATER_EQUAL 1)
    set(NUM_CORES 1)
endif()

set(BUILD_COMMAND
    ${CMAKE_COMMAND}
    --build ${BUILD_DIR}
    --config ${CMAKE_BUILD_TYPE}
    --parallel ${NUM_CORES}
)
message(STATUS "Building with ${NUM_CORES} parallel cores...")

# Avoid inheriting machine-local vcpkg integration from developer environments.
set(_PREV_VCPKG_LOCALAPPDATA_DISABLED "$ENV{VCPkgLocalAppDataDisabled}")
set(ENV{VCPkgLocalAppDataDisabled} 1)

set(_USE_VSDEVCMD_WRAPPER OFF)
set(_BUILD_WRAPPER "")
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows"
   AND GENERATOR STREQUAL "NMake Makefiles"
   AND DEFINED VS_DEVCMD
   AND EXISTS "${VS_DEVCMD}")
    set(_USE_VSDEVCMD_WRAPPER ON)
    set(_BUILD_WRAPPER "${BUILD_DIR}/nmake_build.cmd")
    create_vsdevcmd_wrapper_from_list("${_BUILD_WRAPPER}" BUILD_COMMAND)
endif()

run_with_optional_vsdevcmd_wrapper(
    ${_USE_VSDEVCMD_WRAPPER}
    "${_BUILD_WRAPPER}"
    BUILD_COMMAND
    "${ROOT_DIR}"
    BUILD_RESULT
    BUILD_OUTPUT
    BUILD_ERROR
)

if(_PREV_VCPKG_LOCALAPPDATA_DISABLED STREQUAL "")
    unset(ENV{VCPkgLocalAppDataDisabled})
else()
    set(ENV{VCPkgLocalAppDataDisabled} "${_PREV_VCPKG_LOCALAPPDATA_DISABLED}")
endif()

if(NOT BUILD_RESULT EQUAL 0)
    message(FATAL_ERROR "BUILD FAILED with BUILD_RESULT ${BUILD_RESULT}\n${BUILD_OUTPUT}\n${BUILD_ERROR}")
endif()

message(STATUS "Build completed successfully")