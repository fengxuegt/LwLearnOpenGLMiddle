//
// Created by 心心旺旺 on 2024/10/21.
//

#pragma once
#include ".././glframework/core.h"

class Camera {
public:
    void test(); // 测试cmake配置是否正确
    Camera();
    ~Camera();
    glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();
    virtual void scale(float scale);
public:
    glm::vec3 mPosition{0.0f, 0.0f, 5.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};

};


