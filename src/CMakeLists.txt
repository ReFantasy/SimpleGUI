AUX_SOURCE_DIRECTORY(. SRC_LIST)
add_library(gui STATIC ${SRC_LIST})

# 指定 gui 库的安装路径
file(GLOB Header *.h)
install (TARGETS gui DESTINATION lib)
install (FILES ${Header} DESTINATION include)
