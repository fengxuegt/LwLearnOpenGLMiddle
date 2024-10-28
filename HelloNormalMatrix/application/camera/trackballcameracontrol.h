#pragma once
#include <cameracontrol.h>

class TrackBallCameraControl : public CameraControl{
public:
    TrackBallCameraControl();
    ~TrackBallCameraControl();
    void update() override;

    void onCursor(double xPos, double yPos) override;
    void onKey(int key, int action, int mods) override;
    void onScroll(float offset) override;


private:
    void pitch(float angle);
    void yaw(float angle);
};
