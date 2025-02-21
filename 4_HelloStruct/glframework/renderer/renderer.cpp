//
// Created by 心心旺旺 on 2024/10/24.
//

#include "renderer.h"

#include <check_error.h>
#include <iostream>
#include <ostream>

#include "mesh.h"
#include "material/phonematerial.h"

Renderer::Renderer() {
    mPhongShader = new Shader("assets/shaders/phong.vert","assets/shaders/phong.frag");
}

Renderer::~Renderer() {
}

void Renderer::render(const std::vector<Mesh *> &meshes, Camera *camera, Directionallight *light,
    Ambientlight *ambient) {
    // 设置当前帧绘制的时候，OpenGL的状态机参数
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // 清理画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 绘制mesh
    for (unsigned int i = 0; i < meshes.size(); i++) {
        Mesh *mesh = meshes[i];
        Geometry *geometry = mesh->mGeometry;
        auto material = mesh->mMaterial;

        // 决定使用哪个shader
        Shader *shader = pickShader(material->mType);
        shader->begin();
        // 更新shader中的uniform
        // diffuse 贴图

        switch (material->mType) {
            case MaterialType::PhongMaterial: {
                // 将纹理单元与采样器联系起来
                shader->setInt("texture1",0);
                shader->setInt("texture2",1);
                Phonematerial *phMaterial = (Phonematerial *)material;
                phMaterial->mDiffuse->bind();
                // mvp变换矩阵 modelMatrix
                shader->setMat4("transform", mesh->getModelMatrix());

                // viewMatrix
                shader->setMat4("viewMatrix", camera->getViewMatrix());

                // perspectiveMatrix
                shader->setMat4("perspectiveMatrix", camera->getProjectionMatrix());

                //光源参数的uniform更新
                shader->setVec3("lightDirection", light->mDirection);
                shader->setVec3("lightColor", light->mColor);
                shader->setFloat("lightIntensity", light->mSpecularIntensity);
                shader->setVec3("ambientColor", ambient->mColor);
                auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(mesh->getModelMatrix())));
                shader->setMat3("normalMatrix", normalMatrix);
                shader->setFloat("shiness", phMaterial->mShininess);
                // 相机参数更新
                shader->setVec3("cameraPosition", camera->mPosition);
                break;
            }
            default:
                break;
        }
        // 绑定vao
        GL_LW_CALL(glBindVertexArray(geometry->getVAO()));
        // 执行绘制指令
        GL_LW_CALL(glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0));
        // 解绑VAO
        GL_LW_CALL(glBindVertexArray(0));

        shader->end();
    }
}

Shader * Renderer::pickShader(MaterialType type) {
    Shader * shader = nullptr;
    switch (type) {
        case MaterialType::PhongMaterial:
            shader = mPhongShader;
            break;
        default:
            std::cout << "Unknown material type" << std::endl;
            break;
    }
    return shader;
}
