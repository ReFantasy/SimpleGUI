AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_library(assimp_model ${SRC_LIST} model.h)
target_link_libraries(assimp_model assimp)
