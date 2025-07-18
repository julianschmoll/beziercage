cmake_minimum_required(VERSION 3.15)
project(cage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAYA_CXX_FLAGS}")
SET(LBFGSPP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ext/LBFGSpp/include)
find_package(Maya REQUIRED)
find_path(EIGEN3_INCLUDE_DIR Eigen/Core
        PATHS
        ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include
        ${CMAKE_SOURCE_DIR}/vcpkg/installed/${VCPKG_TARGET_TRIPLET}/include
)
if(NOT EIGEN3_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find Eigen/Core for Eigen3!")
endif()

set(SOURCE_FILES
        common.cpp
        common.hpp
        pluginMain.cpp
        cageCmd.cpp
        cageCmd.hpp
        cageDeformer.cpp
        cageDeformer.hpp
        offsetPin.hpp
        offsetPin.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
        ${LBFGSPP_INCLUDE_DIR}
        ${MAYA_INCLUDE_DIR}
        ${EIGEN3_INCLUDE_DIR}
)
link_directories(${MAYA_LIBRARY_DIR})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION cage/plug-ins)
