cmake_minimum_required(VERSION 3.9)

# Defines project-specific attributes (PROJECT_xxx and baz_xxx)
# https://cmake.org/cmake/help/v3.11/command/project.html
project(bar VERSION 0.0.1 LANGUAGES CXX)

# This include defines standard install locations.
# https://cmake.org/cmake/help/v3.11/module/GNUInstallDirs.html
include(GNUInstallDirs)

# This will allow us to print a feature summary.
# https://cmake.org/cmake/help/v3.11/module/FeatureSummary.html
include(FeatureSummary)

# This include provides some helper functions that simplify packaging.
# https://cmake.org/cmake/help/v3.11/module/CMakePackageConfigHelpers.html
include(CMakePackageConfigHelpers)

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
find_package(foo 0.1.2 CONFIG REQUIRED)

# Only public header files go here.
set(HEADER_FILES
        include/bar/bar.h)

# All source files and private header files go here.
set(SOURCE_FILES
        src/bar.cpp)

# Here we define the library.
add_library(bar
        ${HEADER_FILES}
        ${SOURCE_FILES})

# We also add an alias definition so that we shadown
# the export namespace when using add_subdirectory() instead.
add_library(bar::bar ALIAS bar)

# We now link to all packages.
target_link_libraries(bar
        PUBLIC foo::foo)

# Required compiler features.
# https://cmake.org/cmake/help/v3.1/manual/cmake-compile-features.7.html
target_compile_features(bar
        # Features required to compile the library itself.
        PRIVATE cxx_std_11)

# By prefixing the installation paths with our name and version
# we can have multiple versions installed at the same time.
set(PROJECT_PREFIX bar-${bar_VERSION})

# Defines the headers for this library.
# https://cmake.org/cmake/help/v3.11/command/target_include_directories.html
target_include_directories(bar
        PUBLIC
            # Used when building the library:
            $<BUILD_INTERFACE:${bar_SOURCE_DIR}/include>
            # Used when installing the library:
            $<INSTALL_INTERFACE:include/${PROJECT_PREFIX}>
        PRIVATE
            # Used only when building the library:
            src)

# Here we configure variables specifying the target directories.
set(INSTALL_RUNTIME_DIR ${CMAKE_INSTALL_BINDIR})
set(INSTALL_CONFIG_DIR  ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/cmake)
set(INSTALL_LIBRARY_DIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/${CMAKE_BUILD_TYPE})
set(INSTALL_ARCHIVE_DIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/${CMAKE_BUILD_TYPE}/static)
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_PREFIX}/bar)

# Define the configuration file locations.
set(PROJECT_CONFIG_VERSION_FILE "${PROJECT_BINARY_DIR}/bar-config-version.cmake")
set(PROJECT_CONFIG_FILE         "${PROJECT_BINARY_DIR}/bar-config.cmake")

configure_package_config_file(cmake/bar-config.cmake.in
        ${PROJECT_CONFIG_FILE}
        INSTALL_DESTINATION ${INSTALL_CONFIG_DIR})

# This auto-generates a version file.
write_basic_package_version_file(
        ${PROJECT_CONFIG_VERSION_FILE}
        COMPATIBILITY SameMajorVersion)

# The INSTALL(TARGET) command specifies where to install specific targets.
# By specifying EXPORT here, we add these targets to an export group.
install(TARGETS bar
        EXPORT bar-targets
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR})

# The INSTALL(FILES) command specifies where to install specific files, such as headers.
install(FILES ${HEADER_FILES}
        DESTINATION ${INSTALL_INCLUDE_DIR})

# The INSTALL(FILES) command specifies where to install specific files, such as headers.
install(FILES
            ${PROJECT_CONFIG_VERSION_FILE}
            ${PROJECT_CONFIG_FILE}
        DESTINATION ${INSTALL_CONFIG_DIR})

# The INSTALL(EXPORT) command installs a previously defined export group to a script.
install(EXPORT bar-targets
        FILE bar-targets.cmake
        NAMESPACE bar::
        DESTINATION ${INSTALL_CONFIG_DIR})

export(EXPORT bar-targets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/bar-targets.cmake
       NAMESPACE bar::)

# Register the package in the user's package registry.
# https://cmake.org/cmake/help/v3.11/command/export.html
export(PACKAGE bar)

# Print a summary of the features.
feature_summary(WHAT ALL)
