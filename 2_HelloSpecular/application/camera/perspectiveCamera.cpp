//
// Created by 心心旺旺 on 2024/10/21.
//

#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar) {
    mFovy = fov;
    mAspectRatio = aspect;
    mNear = zNear;
    mFar = zFar;
}

PerspectiveCamera::~PerspectiveCamera() {

}

glm::mat4 PerspectiveCamera::getProjectionMatrix() {
    // 注意这里传入的是角度，需要转化为弧度制
    return glm::perspective(glm::radians(mFovy), mAspectRatio, mNear, mFar);
}

void PerspectiveCamera::scale(float scale) {
    auto front = glm::cross(mUp, mRight);
    mPosition += front * scale;
}
