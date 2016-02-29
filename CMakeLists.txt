#
# Copyright (C) 2013-2014
# Sebastian Schmitz <sschmitz@informatik.uni-siegen.de>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

#
# CMake init stuff
#
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
cmake_policy(SET CMP0015 NEW)

add_definitions(-std=c++0x -g)

#
# Project name and languages
#
project(eqOgre C CXX)

#
# Main application: eqOgre
#
find_package(GLUT REQUIRED)
find_package(Equalizer REQUIRED EQUALIZER)
find_package(Boost REQUIRED system)
find_package(PkgConfig REQUIRED)
find_package(MPI REQUIRED)
pkg_check_modules(OGRE REQUIRED OGRE)

include_directories(
    ${EQUALIZER_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}
    ${GLEWMX_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${MPI_CXX_INCLUDE_PATH}
    ${OGRE_INCLUDE_DIRS}
)


link_directories(
    ${EQUALIZER_LIBRARY_DIRS}
    ${GLUT_LIBRARY_DIRS}
    ${GLEWMX_LIBRARY_DIRS}
    ${Boost_LIBRARY_DIRS}
    ${OGRE_LIBRARY_DIRS}
)

# Definition of CO_IGNORE_BYTESWAP to solve an undefined reference, see http://software.1713.n2.nabble.com/Framedata-unresolved-symbol-lunchbox-byteswap-td7583159.html
add_definitions(-DPACKAGE_NAME="eqOgre" -DPACKAGE_VERSION="1.1"
  -DCO_IGNORE_BYTESWAP)

add_executable(eqOgre
  main.cpp

  equalizer/src/channel.cpp
  equalizer/src/config.cpp
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
  ${MPI_CXX_LIBRARIES}
  ${OGRE_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
)

install(TARGETS eqOgre RUNTIME DESTINATION bin)
install(FILES
  configs/vr_lab_simulation.eqc
  DESTINATION configs
)
