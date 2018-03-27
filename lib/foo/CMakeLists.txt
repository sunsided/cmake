cmake_minimum_required(VERSION 3.9)

# Defines project-specific attributes (PROJECT_xxx and foo_xxx)
# https://cmake.org/cmake/help/v3.11/command/project.html
project(foo VERSION 0.1.2 LANGUAGES CXX DESCRIPTION "An installable sample library.")

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

# An example option to configure the library with.
option(ENABLE_AWESOMENESS "Enables awesomeness." ON)

# We pass the option value as a preprocessor macro.
if(ENABLE_AWESOMENESS)
    message(STATUS "Awesomeness is enabled for this build.")
    add_definitions(-DIS_AWESOME=1)
endif(ENABLE_AWESOMENESS)

# Our library requires Boost
find_package(Boost 1.62 REQUIRED
        COMPONENTS date_time)

# Only public header files go here.
set(HEADER_FILES
        include/foo/foo.h)

# All source files and private header files go here.
set(SOURCE_FILES
        src/foo.cpp)

# Here we define the library.
add_library(foo
        ${HEADER_FILES}
        ${SOURCE_FILES})

# We also add an alias definition so that we shadown
# the export namespace when using add_subdirectory() instead.
add_library(foo::foo ALIAS foo)

# We now link to all packages.
target_link_libraries(foo
        PRIVATE
            Boost::date_time)

# Required compiler features.
# https://cmake.org/cmake/help/v3.1/manual/cmake-compile-features.7.html
target_compile_features(foo
        # Features required to compile the library itself.
        PRIVATE cxx_std_11 cxx_auto_type)

# By prefixing the installation paths with our name and version
# we can have multiple versions installed at the same time.
set(PROJECT_PREFIX foo-${foo_VERSION})

# Defines the headers for this library.
# https://cmake.org/cmake/help/v3.11/command/target_include_directories.html
target_include_directories(foo
        PUBLIC
            # Used when building the library:
            $<BUILD_INTERFACE:${foo_SOURCE_DIR}/include>
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
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_PREFIX}/foo)

# Define the configuration file locations.
set(PROJECT_CONFIG_VERSION_FILE "${PROJECT_BINARY_DIR}/foo-config-version.cmake")
set(PROJECT_CONFIG_FILE         "${PROJECT_BINARY_DIR}/foo-config.cmake")

configure_package_config_file(cmake/foo-config.cmake.in
        ${PROJECT_CONFIG_FILE}
        INSTALL_DESTINATION ${INSTALL_CONFIG_DIR})

# This auto-generates a version file.
write_basic_package_version_file(
        ${PROJECT_CONFIG_VERSION_FILE}
        COMPATIBILITY SameMajorVersion)

# The INSTALL(TARGET) command specifies where to install specific targets.
# By specifying EXPORT here, we add these targets to an export group.
install(TARGETS foo
        EXPORT foo-targets
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
install(EXPORT foo-targets
        FILE foo-targets.cmake
        NAMESPACE foo::
        DESTINATION ${INSTALL_CONFIG_DIR})

export(EXPORT foo-targets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/foo-targets.cmake
       NAMESPACE foo::)

# Register the package in the user's package registry.
# https://cmake.org/cmake/help/v3.11/command/export.html
export(PACKAGE foo)

# Print a summary of the features.
feature_summary(WHAT ALL)
