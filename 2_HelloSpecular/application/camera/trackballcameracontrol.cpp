//
// Created by 心心旺旺 on 2024/10/22.
//

#include "trackballcameracontrol.h"

TrackBallCameraControl::TrackBallCameraControl() {
}

TrackBallCameraControl::~TrackBallCameraControl() {
}

void TrackBallCameraControl::update() {
    CameraControl::update();
}

void TrackBallCameraControl::onCursor(double xPos, double yPos) {
    // 调整相机的各类参数
    if (mLeftButtonDown) {
        // 计算经线和纬线的旋转增量角度
        float deltaX = (xPos - mCurrentMouseX) * mSensitivity;
        float deltaY = (yPos - mCurrentMouseY) * mSensitivity;

        // 分开pitch和yawn各自计算
        pitch(-deltaY);
        yaw(-deltaX);
    } else if (mMiddleButtonDown) {
        float deltaX = (xPos - mCurrentMouseX) * mMoveSpeed;
        float deltaY = (yPos - mCurrentMouseY) * mMoveSpeed;

        mCamera->mPosition -= mCamera->mRight * deltaX;
        mCamera->mPosition += mCamera->mUp * deltaY;

    }
    mCurrentMouseX = xPos;
    mCurrentMouseY = yPos;

}

void TrackBallCameraControl::onKey(int key, int action, int mods) {
    CameraControl::onKey(key, action, mods);
}

void TrackBallCameraControl::onScroll(float offset) {
    mCamera->scale(offset * mScale);
}


void TrackBallCameraControl::pitch(float angle) {
    // 鼠标上下移动
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    // 影响当前相机的up向量和位置
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f); // 用vec4给vec3赋值是没问题的，这样会把前面的xyz赋值给vec3
    mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f); // 因为position是一个点，所以这里要添加为1
}

void TrackBallCameraControl::yaw(float angle) {
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f); // 用vec4给vec3赋值是没问题的，这样会把前面的xyz赋值给vec3
    mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
    mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f); // 因为position是一个点，所以这里要添加为1

}
