cmake_minimum_required(VERSION 3.9)

# Defines project-specific attributes (PROJECT_xxx and foo_xxx)
# https://cmake.org/cmake/help/v3.11/command/project.html
project(foo VERSION 0.1.2 LANGUAGES CXX DESCRIPTION "An installable sample library.")

# The default standard to compile against.
set(CMAKE_CXX_STANDARD 11)

# This include defines standard install locations.
# https://cmake.org/cmake/help/v3.11/module/GNUInstallDirs.html
include(GNUInstallDirs)

# This will allow us to print a feature summary.
# https://cmake.org/cmake/help/v3.11/module/FeatureSummary.html
include(FeatureSummary)

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

# We now link to all packages.
target_link_libraries(foo
        Boost::date_time)

# Required compiler features.
# https://cmake.org/cmake/help/v3.1/manual/cmake-compile-features.7.html
target_compile_features(foo
        # Features required to compile the library itself.
        PRIVATE cxx_auto_type)

# Defines the headers for this library.
# https://cmake.org/cmake/help/v3.11/command/target_include_directories.html
target_include_directories(foo
        PUBLIC
            # Used when building the library:
            $<BUILD_INTERFACE:${foo_SOURCE_DIR}/include>
            # Used when installing the library:
            $<INSTALL_INTERFACE:include>
        PRIVATE
            # Used only when building the library:
            src)

# By prefixing the installation paths with our name and version
# we can have multiple versions installed at the same time.
set(PROJECT_PREFIX foo-${foo_VERSION})

install(TARGETS foo
        EXPORT foo
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/static)

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_PREFIX})

# Print a summary of the features.
feature_summary(WHAT ALL)
