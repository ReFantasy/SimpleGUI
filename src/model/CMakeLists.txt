AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_library(model STATIC ${SRC_LIST} Line.cpp Line.h)

#FILE(GLOB HEADER_FILE ./*.h ./*.hpp) #所有头文件存入变量
#file(COPY ${HEADER_FILE} DESTINATION ${PROJECT_SOURCE_DIR}/install/include)
