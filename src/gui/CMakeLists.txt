AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_library(gui STATIC ${SRC_LIST} gui_base.h gui.h 
../model/mesh.cpp 
../model/mesh.h glsl_shader.h camera.cpp camera.h stb_image.h 
../model/sphere.cpp 
../model/sphere.h 
scene.cpp scene.h glsl_shader.cpp)



#FILE(GLOB HEADER_FILE ./*.h ./*.hpp) #所有头文件存入变量
#file(COPY ${HEADER_FILE} DESTINATION ${PROJECT_SOURCE_DIR}/install/include)
