

#include_directories("${BREW_DIR}/Cellar/glew/2.2.0_1/include")
include_directories(${PROJECT_SOURCE_DIR}/third/glew-2.2.0/include)

include_directories(${PROJECT_SOURCE_DIR}/third/glfw-3.3.8/include)
include_directories("${PROJECT_SOURCE_DIR}/src/gui")
include_directories("${PROJECT_SOURCE_DIR}/src/model")


add_subdirectory(gui)
add_subdirectory(model)

#add_subdirectory(ext)
