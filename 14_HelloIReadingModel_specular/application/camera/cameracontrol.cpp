
#include "cameracontrol.h"

#include <iostream>
#include <ostream>

CameraControl::CameraControl() {
}

CameraControl::~CameraControl() {
}

void CameraControl::onMouse(int button, int action, double xPos, double yPos) {
    // 判断当前按键是否按下
    // std::cout << "CameraControl::onMouse()" << std::endl;
    bool pressed = action == GLFW_PRESS ? true : false;
    if (pressed) {
        mCurrentMouseX = xPos;
        mCurrentMouseY = yPos;
    }
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mLeftButtonDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mRightButtonDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mMiddleButtonDown = pressed;
            break;
    }
}

void CameraControl::onCursor(double xPos, double yPos) {
}

void CameraControl::onKey(int key, int action, int mods) {
    // 检测是否按下或者抬起
    if (action == GLFW_REPEAT) {
        return;
    }
    bool pressed = action == GLFW_PRESS ? true : false;
    // std::cout << "pressed " << pressed << std::endl;
    mKeyMap[key] = pressed;
}

void CameraControl::onScroll(float offset) {
    mCamera->scale(offset);
}

void CameraControl::update() {

}
