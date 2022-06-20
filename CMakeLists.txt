cmake_minimum_required(VERSION 3.0)
project(GUI)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE Release)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )
link_libraries(${OPENGL_LIBRARIES})

# GLFW
include_directories("/opt/homebrew/Cellar/glfw/3.3.7/include")
link_directories("/opt/homebrew/Cellar/glfw/3.3.7/lib")
link_libraries(glfw)

# GLAD
include_directories(${CMAKE_SOURCE_DIR}/ext/glad/include/)

# EIGEN
include_directories("/opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3")


AUX_SOURCE_DIRECTORY(. SRC_LIST)
list(APPEND SRC_LIST ${CMAKE_SOURCE_DIR}/ext/glad/src/glad.c)
add_executable(gui  ${SRC_LIST} gui.h)

