# If you want to build this module without Equalizer, call cmake with -D_NO_EQ=1

#
# CMake init stuff
#
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
cmake_policy(SET CMP0015 NEW)

ADD_DEFINITIONS(-std=c++11) # -Wno-write-strings <- so that DTrack.cpp does not complain anymore

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/equalizer/DynCalib")
    add_subdirectory(equalizer/DynCalib)
    add_definitions(-DUSE_DYNCALIB)
endif()

#
# Installed library: Equalizer
#
find_package(GLEWMX REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
pkg_check_modules(EQUALIZER REQUIRED Equalizer)
include_directories(
  ${EQUALIZER_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIR}
  ${GLEWMX_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
)
add_library(libeqrenderer STATIC
  equalizer/eqserialization.cpp
  equalizer/initdata.cpp
  equalizer/framedata.cpp
  equalizer/config.cpp
  equalizer/node.cpp
  equalizer/pipe.cpp
  equalizer/window.cpp
  equalizer/channel.cpp
  equalizer/nodefactory.cpp
  equalizer/serializableogreactor.cpp
  equalizer/serializablediffactor.cpp
  equalizer/DTrack.cpp
  eqrenderer.cpp
  eqview.cpp
)
link_directories(
    ${EQUALIZER_LIBRARY_DIRS}
    ${GLUT_LIBRARY_DIRS}
    ${GLEWMX_LIBRARY_DIRS}
    ${BULLET_LIBRARY_DIRS}
    ${Boost_LIBRARY_DIR}
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/equalizer/DynCalib")
    target_link_libraries(libeqrenderer
        libdyncalib
    ${EQUALIZER_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${GLEWMX_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    )
else()
    target_link_libraries(libeqrenderer
    ${EQUALIZER_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${GLEWMX_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    )

endif()

set_target_properties(libeqrenderer PROPERTIES OUTPUT_NAME eqrenderer)



