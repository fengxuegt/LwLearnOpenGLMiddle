#pragma once
#include <shader.h>
#include <vector>

#include "../../application/camera/camera.h"
#include "light/ambientlight.h"
#include "light/directionallight.h"
#include "light/pointlight.h"
#include "material/material.h"
class Mesh;

class Renderer {
public:
    Renderer();
    ~Renderer();

    // 渲染功能函数，每次调用，渲染一帧
    void render(const std::vector<Mesh*> &meshes,
        Camera *camera,
        Directionallight *light,
        Ambientlight *ambient
        );
    void render(const std::vector<Mesh*> &meshes,
        Camera *camera,
        PointLight *light,
        Ambientlight *ambient
    );

private:
    Shader *mPhongShader{nullptr};
    Shader *mWhiteShader{nullptr};
    Shader *pickShader(MaterialType type);

};
