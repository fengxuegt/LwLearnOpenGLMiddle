cmake_minimum_required(VERSION 3.10)
project(HelloReadingModel_specular)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DDEBUG)

# 添加 GLAD
# add_library(glad src/glad.c)
include_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
		${ASSIMP_INCLUDE_DIRS}
)
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)



add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)
add_subdirectory(imgui)

# 添加可执行文件
add_executable(HelloReadingModel_specular src/main.cpp src/glad.c)
 
# 链接库
target_link_libraries(HelloReadingModel_specular wrapper glfw.3.dylib application glframework imgui libassimp.5.dylib)

set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_TARGET_DIR "${CMAKE_BINARY_DIR}/assets")

# 添加自定义命令，编译后将 assets 复制到可执行文件所在的目录
add_custom_command(
    TARGET HelloReadingModel_specular POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_SOURCE_DIR}
    ${ASSETS_TARGET_DIR}
)
