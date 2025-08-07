set(SOURCE_FILES
        "common.cpp"
        "common.hpp"
        "cageCmd.cpp"
        "cageCmd.hpp"
        "cageDeformer.cpp"
        "cageDeformer.hpp"
        "offsetPin.hpp"
        "offsetPin.cpp"
        "pluginMain.cpp"
)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAYA_CXX_FLAGS}")
find_package(Maya REQUIRED)
find_package(Eigen3 REQUIRED CONFIG)

link_directories(${MAYA_LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# We can use SYSTEM PUBLIG to avoid warnings from external libraries
target_include_directories(${PROJECT_NAME} PUBLIC
        ${MAYA_INCLUDE_DIR}
        "${CMAKE_SOURCE_DIR}/external/LBFGSpp/include"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${MAYA_LIBRARIES}
        Eigen3::Eigen
)

MAYA_PLUGIN(${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION cage/plug-ins)
