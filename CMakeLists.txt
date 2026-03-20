cmake_minimum_required(VERSION 3.5)
project(cage)

set(PROJECT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT})
set(CMAKE_INSTALL_PREFIX ${PROJECT_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native")
    message("Setting release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")
endif()

# 1: Error, 2: Info, 3: Debug
if(NOT DEFINED LOG_LEVEL)
    set(LOG_LEVEL 0)
endif()

add_subdirectory(src)

target_compile_definitions(cage PUBLIC LOG_LEVEL=${LOG_LEVEL})
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/module.mod" "${PROJECT_PATH}/${PROJECT_NAME}.mod")

install(DIRECTORY scripts DESTINATION ${PROJECT_NAME})
install(DIRECTORY data/icons DESTINATION ${PROJECT_NAME})
install(FILES data/USAGE.md DESTINATION ${CMAKE_BINARY_DIR})
install(FILES src/cageCreator/cageCreator.py DESTINATION ${PROJECT_NAME}/plug-ins)
