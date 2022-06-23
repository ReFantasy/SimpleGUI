AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_library(gui ${SRC_LIST} gui_base.h gui.h mesh.cpp mesh.h glsl_shader.h camera.cpp camera.h stb_image.h)
target_link_libraries(gui)
