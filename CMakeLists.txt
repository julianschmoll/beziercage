cmake_minimum_required(VERSION 3.5)
project(cage)

set(PROJECT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT})
set(CMAKE_INSTALL_PREFIX ${PROJECT_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

add_subdirectory(src)

# 1: Error, 2: Info, 3: Debug
if(NOT DEFINED LOG_LEVEL)
    set(LOG_LEVEL 0)
endif()

target_compile_definitions(cage PUBLIC LOG_LEVEL=${LOG_LEVEL})
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/module.mod" "${PROJECT_PATH}/${PROJECT_NAME}.mod")

install(DIRECTORY scripts DESTINATION ${PROJECT_NAME})
install(DIRECTORY data/icons DESTINATION ${PROJECT_NAME})
install(FILES data/USAGE.md DESTINATION ${CMAKE_BINARY_DIR})
install(FILES src/cageCreator.py DESTINATION ${PROJECT_NAME}/plug-ins)
