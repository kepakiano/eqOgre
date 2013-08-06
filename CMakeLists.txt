# Copyright (C) 2012
# Martin Lambers <marlam@marlam.de>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice and this
# notice are preserved. This file is offered as-is, without any warranty.

#
# CMake init stuff
#
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
cmake_policy(SET CMP0015 NEW)

add_definitions(-std=c++11)

#
# Project name and languages
#
project(eqOgre C CXX)

#
# Main application: VRCalib
#
find_package(GLUT REQUIRED)
find_package(PkgConfig)
pkg_check_modules(EQUALIZER REQUIRED Equalizer)
pkg_check_modules(OGRE REQUIRED OGRE)

include_directories(
    ${EQUALIZER_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}
    ${GLEWMX_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${OGRE_INCLUDE_DIRS}
)

link_directories(
    ${EQUALIZER_LIBRARY_DIRS}
    ${GLUT_LIBRARY_DIRS}
    ${GLEWMX_LIBRARY_DIRS}
    ${OGRE_LIBRARIES}
)

add_definitions(-DPACKAGE_NAME="eqOgre" -DPACKAGE_VERSION="1.0")

add_executable(eqOgre
  main.cpp

  equalizer/src/channel.cpp
  equalizer/src/config.cpp
  equalizer/src/eqserialization.cpp
  equalizer/src/framedata.cpp
  equalizer/src/initdata.cpp
  equalizer/src/node.cpp
  equalizer/src/nodefactory.cpp
  equalizer/src/pipe.cpp
  equalizer/src/serializablediffactor.cpp
  equalizer/src/serializableogreactor.cpp
  equalizer/src/window.cpp

  ogre/src/ogreapplication.cpp

  datastructures/src/ogreactor.cpp
  datastructures/src/diffactor.cpp
  datastructures/headers/vec3.h
  datastructures/headers/vec4.h
)
set_target_properties(eqOgre PROPERTIES OUTPUT_NAME eqOgre)
target_link_libraries(eqOgre
  ${EQUALIZER_LIBRARIES}
  ${GLUT_LIBRARIES}
  ${GLEWMX_LIBRARIES}
  ${OPENGL_gl_LIBRARY}
  ${OPENGL_glu_LIBRARY}
  ${OGRE_LIBRARIES}
)



install(TARGETS eqOgre RUNTIME DESTINATION bin)
install(FILES
  configs/config-vrlab-12node.eqc  configs/config-vrlab.eqc  configs/config-vrlab-simulation.eqc
  DESTINATION share/eqFlyingThings
)
