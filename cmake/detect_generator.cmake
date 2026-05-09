## @file    detect_generator.cmake
## @brief   Identify host system and choose a robust build generator.
## @details Detects platform/arch/cores and chooses a generator with practical
##          priority rules. Also exports optional `PLATFORM` and `VS_DEVCMD`
##          values used by wrapper scripts when NMake needs a VS environment.

cmake_minimum_required(VERSION 3.28)

if(WIN32)
    set(DETECTED_PLATFORM "Windows")
elseif(APPLE)
    set(DETECTED_PLATFORM "macOS")
elseif(UNIX)
    set(DETECTED_PLATFORM "Linux")
else()
    set(DETECTED_PLATFORM "Unknown")
endif()

if(DEFINED ENV{PROCESSOR_ARCHITECTURE} AND NOT "$ENV{PROCESSOR_ARCHITECTURE}" STREQUAL "")
    set(DETECTED_ARCH "$ENV{PROCESSOR_ARCHITECTURE}")
else()
    set(DETECTED_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
endif()

include(ProcessorCount)
ProcessorCount(NUM_CORES)
if(NOT NUM_CORES GREATER_EQUAL 1)
    set(NUM_CORES 1)
endif()

set(PLATFORM "")
unset(VS_DEVCMD)

# Honor a user-selected generator if explicitly provided.
if(DEFINED CMAKE_GENERATOR AND NOT "${CMAKE_GENERATOR}" STREQUAL "")
    set(GENERATOR "${CMAKE_GENERATOR}")
    if(GENERATOR MATCHES "Visual Studio")
        set(PLATFORM "-A x64")
    endif()
else()
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        set(_vs_found FALSE)

        find_program(VS2022_MSBUILD msbuild.exe
            PATHS
                "C:/Program Files/Microsoft Visual Studio/2022/Enterprise/MSBuild/Current/Bin"
                "C:/Program Files/Microsoft Visual Studio/2022/Professional/MSBuild/Current/Bin"
                "C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin"
            NO_DEFAULT_PATH
        )
        if(VS2022_MSBUILD)
            set(GENERATOR "Visual Studio 17 2022")
            set(PLATFORM "-A x64")
            get_filename_component(_vs_msbuild_bin "${VS2022_MSBUILD}" DIRECTORY)
            get_filename_component(_vs_msbuild_current "${_vs_msbuild_bin}" DIRECTORY)
            get_filename_component(_vs_msbuild_dir "${_vs_msbuild_current}" DIRECTORY)
            get_filename_component(_vs_install_root "${_vs_msbuild_dir}" DIRECTORY)
            set(VS_DEVCMD "${_vs_install_root}/Common7/Tools/VsDevCmd.bat")
            set(_vs_found TRUE)
        endif()

        if(NOT _vs_found)
            find_program(VS2019_MSBUILD msbuild.exe
                PATHS
                    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/MSBuild/Current/Bin"
                    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/MSBuild/Current/Bin"
                    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin"
                NO_DEFAULT_PATH
            )
            if(VS2019_MSBUILD)
                set(GENERATOR "Visual Studio 16 2019")
                set(PLATFORM "-A x64")
                get_filename_component(_vs_msbuild_bin "${VS2019_MSBUILD}" DIRECTORY)
                get_filename_component(_vs_msbuild_current "${_vs_msbuild_bin}" DIRECTORY)
                get_filename_component(_vs_msbuild_dir "${_vs_msbuild_current}" DIRECTORY)
                get_filename_component(_vs_install_root "${_vs_msbuild_dir}" DIRECTORY)
                set(VS_DEVCMD "${_vs_install_root}/Common7/Tools/VsDevCmd.bat")
                set(_vs_found TRUE)
            endif()
        endif()

        if(NOT _vs_found)
            find_program(NINJA_PATH ninja)
            if(NINJA_PATH)
                set(GENERATOR "Ninja")
            else()
                find_program(CL_COMPILER cl.exe)
                if(CL_COMPILER)
                    set(GENERATOR "NMake Makefiles")
                else()
                    set(GENERATOR "")
                endif()
            endif()
        endif()

        # CMake 4.x dropped support for VS2022 generator; prefer NMake with VS env.
        if(GENERATOR STREQUAL "Visual Studio 17 2022"
           AND CMAKE_VERSION VERSION_GREATER_EQUAL "4.0"
           AND DEFINED VS_DEVCMD
           AND EXISTS "${VS_DEVCMD}")
            set(GENERATOR "NMake Makefiles")
            set(PLATFORM "")
        endif()
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
        find_program(NINJA_PATH ninja)
        if(NINJA_PATH)
            set(GENERATOR "Ninja")
        else()
            set(GENERATOR "Unix Makefiles")
        endif()
    else()
        set(GENERATOR "")
    endif()
endif()

message("")
message("======= Build Platform and System Architecture Detection ======================")
message(STATUS "Platform:      ${DETECTED_PLATFORM} (${DETECTED_ARCH})")
message(STATUS "Generator:     ${GENERATOR}")
if(PLATFORM)
    message(STATUS "Platform Arg:  ${PLATFORM}")
endif()
if(DEFINED VS_DEVCMD AND EXISTS "${VS_DEVCMD}")
    message(STATUS "VS Dev Env:    ${VS_DEVCMD}")
endif()
message(STATUS "CPU Cores:     ${NUM_CORES}")
