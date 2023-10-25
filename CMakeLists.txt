cmake_minimum_required(VERSION 3.25.0-rc4)
project(data-structure)

set(cmake_c_compiler "gcc")
set(cmake_cxx_compiler "g++")
set(cmake_c_standard 17)
set(cmake_cxx_standard 17)
set(cmake_cxx_extensions OFF)
set(cmake_export_complie_commands on)

# 设置静态库名称
set(ch02_list_lib)


# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(utils)
