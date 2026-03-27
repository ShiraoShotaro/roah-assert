cmake_minimum_required(VERSION 3.30)

project(roah-assert
    VERSION
        1.0.0
    DESCRIPTION
        "Roah Assert Utility"
    LANGUAGES
        CXX
)

add_compile_options(
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/EHsc>"
    "$<$<CXX_COMPILER_ID:MSVC>:/MP>"
    "$<$<CXX_COMPILER_ID:MSVC>:/W4>"
    "$<$<CXX_COMPILER_ID:MSVC>:/WX>"

    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
)
add_compile_definitions(
    "$<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>"
    "$<$<CXX_COMPILER_ID:MSVC>:WIN32_LEAN_AND_MEAN>"
)

# --- LIBRARY ---
add_library(roah-assert)
set_target_properties(roah-assert
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
target_sources(roah-assert
    PRIVATE
        src/assert.cpp

    PUBLIC
        FILE_SET
            HEADERS
        TYPE
            HEADERS
        BASE_DIRS
            include
        FILES
            include/roah/assert.hpp
)
target_compile_definitions(roah-assert
    PUBLIC
        "$<$<CONFIG:Debug>:ROAH_DEBUG>"
)
install(
    TARGETS roah-assert
    EXPORT ${CMAKE_PROJECT_NAME}-export
    FILE_SET HEADERS
)

# --- INSTALL ---
install (
    EXPORT
        ${CMAKE_PROJECT_NAME}-export
    FILE
        ${CMAKE_PROJECT_NAME}Targets.cmake
    DESTINATION
        lib/cmake/${CMAKE_PROJECT_NAME}
    NAMESPACE
        ${CMAKE_PROJECT_NAME}::
    EXPORT_LINK_INTERFACE_LIBRARIES
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
        "lib/cmake/${CMAKE_PROJECT_NAME}"
    NO_SET_AND_CHECK_MACRO
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
    VERSION
        "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}"
    COMPATIBILITY
        AnyNewerVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION
        "lib/cmake/${CMAKE_PROJECT_NAME}"
)
