# 创建静态库 (或动态库，如果需要)
add_library(wrapper STATIC check_error.cpp)

# 将 wrapper 目录的头文件路径设置为 PUBLIC，使主项目也可以访问
target_include_directories(wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
