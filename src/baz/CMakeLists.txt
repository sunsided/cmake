cmake_minimum_required(VERSION 3.9)

# Defines project-specific attributes (PROJECT_xxx and baz_xxx)
# https://cmake.org/cmake/help/v3.11/command/project.html
project(baz VERSION 0.0.0 LANGUAGES CXX)

# This include defines standard install locations.
# https://cmake.org/cmake/help/v3.11/module/GNUInstallDirs.html
include(GNUInstallDirs)

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

# This project depends on the foo package.
find_package(bar CONFIG REQUIRED)

# All source files and private header files go here.
set(SOURCE_FILES
        src/main.cpp)

# Here we define the executable.
add_executable(baz
        ${SOURCE_FILES})

# We now link to all packages.
target_link_libraries(baz
        PRIVATE bar::bar)

# Required compiler features.
# https://cmake.org/cmake/help/v3.1/manual/cmake-compile-features.7.html
target_compile_features(baz
        # Features required to compile the binary itself.
        PRIVATE cxx_std_11)

# Defines the headers for this binary.
# https://cmake.org/cmake/help/v3.11/command/target_include_directories.html
target_include_directories(baz
        PRIVATE
            # Used only when building the binary:
            src)

# By prefixing the installation paths with our name and version
# we can have multiple versions installed at the same time.
set(PROJECT_PREFIX baz-${baz_VERSION})

# Here we configure variables specifying the target directories.
set(INSTALL_RUNTIME_DIR ${CMAKE_INSTALL_BINDIR})

# The INSTALL(TARGET) command specifies where to install specific targets.
install(TARGETS baz
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR})
