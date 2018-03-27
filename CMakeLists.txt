cmake_minimum_required(VERSION 3.9)

# Allows the usage of the ExternalProject_xxx commands.
# https://cmake.org/cmake/help/v3.11/module/ExternalProject.html
include(ExternalProject)

# Required to enable testing for link-time optimization.
# https://cmake.org/cmake/help/v3.11/module/CheckIPOSupported.html
include(CheckIPOSupported)

# Use link-time optimization if allowed.
check_ipo_supported(RESULT ipo_supported)
if(ipo_supported)
    set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# We attempt to use ccache to speed up the build.
find_program(CCACHE_FOUND "ccache")
if(CCACHE_FOUND)
    message(STATUS "Using ccache for building.")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# If no build type was specified, set it to Release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: None Debug Release."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# If no installation prefix is given manually, install locally.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING
            "The install location"
            FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

add_subdirectory(lib/foo)
add_subdirectory(src/bar)
add_subdirectory(src/baz)