cmake_minimum_required(VERSION 3.0)
project(GUI)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

add_definitions(-DGUI_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
# OpenGL
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )
link_libraries(${OPENGL_LIBRARIES})

# 输出平台信息
IF (WIN32)
    SET(THIRD_LIBS_DIR "F:/ProjectCode/Simulation/third_party/WIN")
    #GLFW
    include_directories("${THIRD_LIBS_DIR}/glfw-3.3.5.bin.WIN64/include")
    link_directories("${THIRD_LIBS_DIR}/glfw-3.3.5.bin.WIN64/lib-vc2019")
    link_libraries(glfw3_mt)

    #GLEW
    include_directories("${THIRD_LIBS_DIR}/glew-2.1.0/include")
    link_directories("${THIRD_LIBS_DIR}/glew-2.1.0/lib/Release/x64")
    link_libraries(glew32s)# #define GLEW_STATIC on top of your code to use the static lib
ELSEIF (APPLE)
    # GLFW
    include_directories("/opt/homebrew/Cellar/glfw/3.3.8/include")
    link_directories("/opt/homebrew/Cellar/glfw/3.3.8/lib")
    include_directories("/usr/local/Cellar/glfw/3.3.8/include")
    link_directories("/usr/local/Cellar/glfw/3.3.8/lib")
    link_libraries(glfw)

    #GLEW
    include_directories("/opt/homebrew/Cellar/glew/2.2.0_1/include")
    link_directories("/opt/homebrew/Cellar/glew/2.2.0_1/lib")
    include_directories("/usr/local/Cellar/glew/2.2.0_1/include")
    link_directories("/usr/local/Cellar/glew/2.2.0_1/lib")
    link_libraries(GLEW)
ELSEIF (UNIX)
    include_directories("/usr/include/")
	include_directories("/usr/local/include/")
    link_directories("/usr/lib")
    link_directories("/usr/local/lib")
    link_directories("/usr/lib64")
    link_directories("/usr/lib/x86_64-linux-gnu/")
    link_libraries(${OPENGL_LIBRARIES} glfw GLEW ${GLSLCOOKBOOK_LIBS})
ENDIF ()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/dear_imgui)
include_directories(${PROJECT_SOURCE_DIR}/third_party/)
include_directories(${PROJECT_SOURCE_DIR}/third_party/GLM)

# 项目源码
add_subdirectory(src)

AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_executable(demo ${SRC_LIST})
target_link_libraries(demo gui)



