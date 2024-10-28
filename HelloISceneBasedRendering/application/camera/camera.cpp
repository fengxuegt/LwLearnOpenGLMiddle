//
// Created by 心心旺旺 on 2024/10/21.
//

#include "camera.h"

#include <iostream>
#include <ostream>

void Camera::test() {
    std::cout << "test" << std::endl;
}

Camera::Camera() {
}

Camera::~Camera() {
}

glm::mat4 Camera::getViewMatrix() {
    // 使用lookat矩阵来生成viewMatrix
    // eye 是相机位置
    // center 是看向世界坐标的哪个点
    // top 穹顶向量
    glm::vec3 front = glm::cross(mUp, mRight);
    glm::vec3 center = mPosition + front;
    return glm::lookAt(mPosition, center, mUp);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::mat4(1.0f);
}

void Camera::scale(float scale) {
}
