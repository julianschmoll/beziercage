set(SOURCE_FILES
        "common.cpp"
        "common.hpp"
        "pluginMain.cpp"
        "cageCmd.cpp"
        "cageCmd.hpp"
        "cageDeformer.cpp"
        "cageDeformer.hpp"
        "cageControlNode.cpp"
        "cageControlNode.hpp"
)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAYA_CXX_FLAGS}")
find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION cage/plug-ins)
