cmake_minimum_required(VERSION 3.9)

# Defines project-specific attributes (PROJECT_xxx and baz_xxx)
# https://cmake.org/cmake/help/v3.11/command/project.html
project(baz VERSION 0.0.0 LANGUAGES CXX)

# The default standard to compile against.
set(CMAKE_CXX_STANDARD 11)

# This include defines standard install locations.
# https://cmake.org/cmake/help/v3.11/module/GNUInstallDirs.html
include(GNUInstallDirs)

# This will allow us to print a feature summary.
# https://cmake.org/cmake/help/v3.11/module/FeatureSummary.html
include(FeatureSummary)

# All source files and private header files go here.
set(SOURCE_FILES
        src/main.cpp)

# Here we define the executable.
add_executable(baz
        ${SOURCE_FILES})

# We now link to all packages.
target_link_libraries(baz
        foo)

# Required compiler features.
# https://cmake.org/cmake/help/v3.1/manual/cmake-compile-features.7.html
target_compile_features(baz
        # Features required to compile the binary itself.
        PRIVATE cxx_auto_type)

# Defines the headers for this binary.
# https://cmake.org/cmake/help/v3.11/command/target_include_directories.html
target_include_directories(baz
        PRIVATE
            # Used only when building the binary:
            src)

set(PROJECT_PREFIX foo-${foo_VERSION})

install(TARGETS baz
        EXPORT baz
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_PREFIX})

# Print a summary of the features.
feature_summary(WHAT ALL)
