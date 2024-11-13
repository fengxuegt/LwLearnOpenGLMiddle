cmake_minimum_required(VERSION 3.10)
project(HelloParentChild)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DDEBUG)

# 添加 GLAD
# add_library(glad src/glad.c)
include_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)





add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)
add_subdirectory(imgui)
# 查找 GLFW
# find_package(OpenGL REQUIRED)
# find_package(glfw3 REQUIRED)

# 添加可执行文件
add_executable(HelloParentChild src/main.cpp src/glad.c)
 
# 链接库
target_link_libraries(HelloParentChild wrapper glfw.3.dylib application glframework imgui)

set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_TARGET_DIR "${CMAKE_BINARY_DIR}/assets")

# 添加自定义命令，编译后将 assets 复制到可执行文件所在的目录
add_custom_command(
    TARGET HelloParentChild POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_SOURCE_DIR}
    ${ASSETS_TARGET_DIR}
)
