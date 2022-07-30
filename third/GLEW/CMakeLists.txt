include_directories("./")
set(SRC_GLEW glew.c glewinfo.c visualinfo.c )
add_library(glew ${SRC_GLEW})
install(TARGETS glew DESTINATION ${PROJECT_SOURCE_DIR}/GLEW/lib)

