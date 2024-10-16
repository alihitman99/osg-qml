cmake_minimum_required(VERSION 3.12)

set(projName osgQml)
project(${projName} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Quick REQUIRED)

add_executable(${projName}
    main.cpp
    osgItem.cpp
    osgRenderNode.cpp
    qml.qrc
    tree.osgb)

target_link_libraries(${projName}
  PRIVATE Qt6::Core Qt6::Quick
  PUBLIC osg osgViewer osgDB osgGA OpenThreads osgManipulator osgSim osgParticle osgText osgUtil
  gdal)

add_custom_command(TARGET ${projName} POST_BUILD
        COMMAND cp ARGS "-rf" "${CMAKE_CURRENT_SOURCE_DIR}/tree.osgb" "${CMAKE_CURRENT_BINARY_DIR}/tree.osgb")
