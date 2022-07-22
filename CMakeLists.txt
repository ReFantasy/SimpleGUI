cmake_minimum_required(VERSION 3.0)
project(GUI)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE Release)

set(BREW_DIR "/usr/local")


if(${CMAKE_SYSTEM_VERSION} STREQUAL "21.6.0")
    set(BREW_DIR "/opt/homebrew")
endif()

add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

# GLFW
include_directories("${BREW_DIR}/Cellar/glfw/3.3.7/include")
link_directories("${BREW_DIR}/Cellar/glfw/3.3.7/lib")
link_libraries(glfw)

#GLEW
include_directories("${BREW_DIR}/Cellar/glew/2.2.0_1/include")
link_directories("${BREW_DIR}/Cellar/glew/2.2.0_1/lib")
link_libraries(glew)

# EIGEN
include_directories("${BREW_DIR}/Cellar/eigen/3.4.0_1/include/eigen3")
# GLM
include_directories("${BREW_DIR}/Cellar/glm/0.9.9.8/include")

# ASSIMP
#add_subdirectory(third)

add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main gui)
