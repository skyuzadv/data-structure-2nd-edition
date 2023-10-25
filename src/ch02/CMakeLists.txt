set (
    SRC_LIST
    01_seqList.hpp
    02_linkList.hpp
    03_duLinkList.hpp
    04_circLinkList.hpp
    05_crduLinkList.hpp
)

# 生成静态库
add_library( 
    ch02_link_list 
    ${SRC_LIST} 
)

# 模板类头文件.hpp生成，强制按照c++语言编译
set_target_properties(ch02_link_list PROPERTIES LINKER_LANGUAGE CXX)
