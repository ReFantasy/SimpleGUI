cmake_minimum_required(VERSION 3.0)
project(GUI)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

set(CMAKE_CXX_STANDARD 17)


add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/third/GLM)



# 输出平台信息
IF (WIN32)
    MESSAGE(STATUS "operating system is windows")
ELSEIF (APPLE)
    MESSAGE(STATUS "operating system is Apple system.")
    find_package(glfw3 REQUIRED)
ELSEIF (UNIX)
	MESSAGE(STATUS "operating system is UNIX-like OS.")
ENDIF ()

# 第三方库源码
add_subdirectory(third)

# 项目源码
add_subdirectory(src)

# 测试程序
include_directories(${PROJECT_SOURCE_DIR}/src/gui)
include_directories(${PROJECT_SOURCE_DIR}/src/model)
add_executable(demo main.cpp)
target_link_libraries(demo gui model glfw glew)



