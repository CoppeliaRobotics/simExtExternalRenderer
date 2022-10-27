cmake_minimum_required(VERSION 3.15)
project(simExtExternalRenderer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_AUTOMOC ON)

find_package(Boost REQUIRED)
find_package(Qt5 COMPONENTS Widgets OpenGL PrintSupport REQUIRED)
find_package(OpenGL REQUIRED)

if(NOT LIBPLUGIN_DIR)
    if(DEFINED ENV{COPPELIASIM_ROOT_DIR})
        set(LIBPLUGIN_DIR $ENV{COPPELIASIM_ROOT_DIR}/programming/libPlugin)
    else()
        set(LIBPLUGIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libPlugin)
    endif()
endif()
list(APPEND CMAKE_MODULE_PATH ${LIBPLUGIN_DIR}/cmake)
find_package(CoppeliaSim 4.1.0.0 REQUIRED)

coppeliasim_add_plugin(
    simExtExternalRenderer
    LEGACY
    SOURCES
    simExtExternalRenderer.cpp
    openglWidget.cpp
    frameBufferObject.cpp
    offscreenGlContext.cpp
    openglOffscreen.cpp
    openglBase.cpp
    ocMesh.cpp
    ocMeshContainer.cpp
    ocTexture.cpp
    ocTextureContainer.cpp
    ${COPPELIASIM_ROOT_DIR}/programming/simMath/MyMath.cpp
    ${COPPELIASIM_ROOT_DIR}/programming/simMath/3X3Matrix.cpp
    ${COPPELIASIM_ROOT_DIR}/programming/simMath/4X4Matrix.cpp
    ${COPPELIASIM_ROOT_DIR}/programming/simMath/MMatrix.cpp
    ${COPPELIASIM_ROOT_DIR}/programming/simMath/3Vector.cpp
    ${COPPELIASIM_ROOT_DIR}/programming/simMath/4Vector.cpp
    ${COPPELIASIM_ROOT_DIR}/programming/simMath/7Vector.cpp
)
target_include_directories(simExtExternalRenderer PRIVATE ${COPPELIASIM_ROOT_DIR}/programming/simMath)
target_link_libraries(simExtExternalRenderer Qt5::Widgets Qt5::OpenGL Qt5::PrintSupport OpenGL::GL)
