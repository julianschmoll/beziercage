cmake_minimum_required(VERSION 3.5)
project(cage)

# ganz oben in CMakeLists.txt einfügen
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(vcpkg_toolchain "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    if(EXISTS "${vcpkg_toolchain}")
        set(CMAKE_TOOLCHAIN_FILE ${vcpkg_toolchain} CACHE STRING "")
    endif()
endif()
set(PROJECT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT})
set(CMAKE_INSTALL_PREFIX ${PROJECT_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

add_subdirectory(src)

# 1: Error, 2: Info, 3: Debug
if(NOT DEFINED LOG_LEVEL)
    set(LOG_LEVEL 1)
endif()

target_compile_definitions(cage PUBLIC LOG_LEVEL=${LOG_LEVEL})
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/module.mod" "${PROJECT_PATH}/${PROJECT_NAME}.mod")

install(DIRECTORY scripts DESTINATION cage)
install(FILES data/USAGE.md DESTINATION ${CMAKE_BINARY_DIR})
