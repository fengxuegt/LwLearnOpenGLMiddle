
#pragma once
#include <map>

#include "camera.h"
#include "../../glframework/core.h"
class CameraControl {
public:
    CameraControl();
    ~CameraControl();

    // 逻辑函数
    virtual void onMouse(int button, int action, double xPos, double yPos);
    virtual void onCursor(double xPos, double yPos);
    virtual void onKey(int key, int action, int mods);
    virtual void onScroll(float offset);

    virtual void update();

    // set函数
    void setCamera(Camera* camera) {
        mCamera = camera;
    }
    void setSensitivity(float sensitivity) {
        mSensitivity = sensitivity;
    }
    void setScale(float scale) {
        mScale = scale;
    }


protected:
    std::map<int, bool> mKeyMap;

    Camera* mCamera;
    // 保存鼠标几个按键是否按下
    bool mRightButtonDown = false;
    bool mLeftButtonDown = false;
    bool mMiddleButtonDown = false;

    // 鼠标位置
    float mCurrentMouseX = 0.0f;
    float mCurrentMouseY = 0.0f;
    // 鼠标灵敏度
    float mSensitivity = 0.1f;

    // 鼠标移动速度
    float mMoveSpeed = 0.05f;
    // 相机的缩放速度
    float mScale = 0.2f;

};


