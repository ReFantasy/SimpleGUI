AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_library(gui ${SRC_LIST} gui_base.h gui.h mesh.cpp mesh.h glsl_shader.h camera.cpp camera.h stb_image.h ../model/sphere.cpp ../model/sphere.h scene.cpp scene.h)
#target_link_libraries(gui)


FILE(GLOB HEADER_FILE ./*.h ./*.hpp) #所有头文件存入变量
# 安装
#INSTALL(TARGETS gui ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/install/lib)
#FOREACH(F ${HEADER_FILE})
#    INSTALL(FILES ${F} DESTINATION ${PROJECT_SOURCE_DIR}/install/include)
#ENDFOREACH(F)

file(COPY ${HEADER_FILE} DESTINATION ${PROJECT_SOURCE_DIR}/install/include)
