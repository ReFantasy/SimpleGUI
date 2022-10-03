cmake_minimum_required(VERSION 3.0)
project(GUI)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

set(CMAKE_CXX_STANDARD 17)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )
link_libraries(${OPENGL_LIBRARIES})

# 输出平台信息
IF (WIN32)
    MESSAGE(STATUS "operating system is windows")
ELSEIF (APPLE)
    MESSAGE(STATUS "operating system is Apple system.")
    include_directories("/opt/homebrew/Cellar/glfw/3.3.8/include")
ELSEIF (UNIX)
	MESSAGE(STATUS "operating system is UNIX-like OS.")
    #GLFW GLEW
    include_directories("/usr/include/")
	include_directories("/usr/local/include/")
    link_directories("/usr/lib")
    link_directories("/usr/local/lib")
    link_directories("/usr/lib64")
    link_directories("/usr/lib/x86_64-linux-gnu/")
    link_libraries(${OPENGL_LIBRARIES} glfw GLEW ${GLSLCOOKBOOK_LIBS})
ENDIF ()


include_directories(${PROJECT_SOURCE_DIR}/third_party/GLM)
include_directories(${PROJECT_SOURCE_DIR}/src)


# 项目源码
add_subdirectory(src)


add_executable(demo main.cpp)
target_link_libraries(demo gui)



