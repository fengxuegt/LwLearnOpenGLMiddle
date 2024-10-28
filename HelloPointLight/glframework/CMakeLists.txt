
# 创建静态库 (或动态库，如果需要)
add_library(glframework STATIC shader.cpp
        Texture.cpp
        Texture.h
        geometry.cpp
        geometry.h
        object.cpp
        object.h
        material/material.cpp
        material/material.h
        material/phonematerial.cpp
        material/phonematerial.h
        mesh.cpp
        mesh.h
        light/light.cpp
        light/light.h
        light/directionallight.cpp
        light/directionallight.h
        light/ambientlight.cpp
        light/ambientlight.h
        renderer/renderer.cpp
        renderer/renderer.h
        material/whitematerial.cpp
        material/whitematerial.h
        light/pointlight.cpp
        light/pointlight.h)

# 将 wrapper 目录的头文件路径设置为 PUBLIC，使主项目也可以访问
target_include_directories(glframework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(glframework PUBLIC wrapper)


