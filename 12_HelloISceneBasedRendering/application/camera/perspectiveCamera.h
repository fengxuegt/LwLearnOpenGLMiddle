//
// Created by 心心旺旺 on 2024/10/21.
//

#pragma once
#include "orthographicCamera.h"


class PerspectiveCamera : public Camera{
public:
    PerspectiveCamera(float fov, float aspect, float zNear, float zFar);
    ~PerspectiveCamera();
    glm::mat4 getProjectionMatrix() override;
    void scale(float scale) override;

private:
    float mFovy = 0.0f;
    float mAspectRatio = 0.0f;
    float mNear = 0.0f;
    float mFar = 0.0f;

};



