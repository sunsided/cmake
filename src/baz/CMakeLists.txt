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

# By prefixing the installation paths with our name and version
# we can have multiple versions installed at the same time.
set(PROJECT_PREFIX baz-${baz_VERSION})

# Here we configure variables specifying the target directories.
set(INSTALL_RUNTIME_DIR ${CMAKE_INSTALL_BINDIR})
set(INSTALL_LIBRARY_DIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/${CMAKE_BUILD_TYPE})
set(INSTALL_ARCHIVE_DIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/${CMAKE_BUILD_TYPE}/static)
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_PREFIX})

# The INSTALL(TARGET) command specifies where to install specific targets.
install(TARGETS baz
        EXPORT baz
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR})

# The INSTALL(FILES) command specifies where to install specific files, such as headers.
install(FILES ${HEADER_FILES}
        DESTINATION ${INSTALL_INCLUDE_DIR})

# Print a summary of the features.
feature_summary(WHAT ALL)
