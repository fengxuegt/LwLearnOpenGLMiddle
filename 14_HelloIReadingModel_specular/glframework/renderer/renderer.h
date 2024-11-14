#pragma once
#include <shader.h>
#include <vector>

#include "scene.h"
#include "../../application/camera/camera.h"
#include "light/ambientlight.h"
#include "light/directionallight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
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
    void render(const std::vector<Mesh*> &meshes,
        Camera *camera,
        SpotLight *light,
        Ambientlight *ambient
    );
    void render(Scene* scene,
        Camera *camera,
        Directionallight *light,
        Ambientlight *ambient
        );
    void renderObject(Object* object,
        Camera *camera,
        Directionallight *light,
        Ambientlight *ambient
    );

    void setClearColor(float r, float g, float b, float a);
    void renderObject(Object * object);

private:
    Shader *mPhongShader{nullptr};
    Shader *mWhiteShader{nullptr};
    Shader *pickShader(MaterialType type);

};
