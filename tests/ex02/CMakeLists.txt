# 包含公共库
include_directories(${CMAKE_SOURCE_DIR}/src/ch02)
# 生成可执行文件
add_executable(test test.cpp)
# 链接公共库
target_link_libraries(test ${ch02_link_list})
