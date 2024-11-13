# 自动收集 ImGui 所有 .cpp 文件
file(GLOB IMGUI_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# 创建 ImGui 静态库
add_library(imgui STATIC ${IMGUI_SOURCES}
        imgui_tables.cpp)

# 将 wrapper 目录的头文件路径设置为 PUBLIC，使主项目也可以访问
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
