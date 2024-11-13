//
// Created by 心心旺旺 on 2024/10/21.
//

#include "orthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) {
    mLeft = left;
    mRight = right;
    mBottom = bottom;
    mTop = top;
    mNear = near;
    mFar = far;
}

OrthographicCamera::~OrthographicCamera() {
}

glm::mat4 OrthographicCamera::getProjectionMatrix() {
    float scale = std::pow(2.0f, mScale);
    return glm::ortho(mLeft * scale, mRight * scale, mBottom * scale, mTop * scale, mNear, mFar);
}

void OrthographicCamera::scale(float scale) {
    mScale += scale;
}
