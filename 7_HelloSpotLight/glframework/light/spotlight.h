#pragma once
#include "light.h"
#include "object.h"

class SpotLight : public Light, public Object{
public:
    SpotLight();
    virtual ~SpotLight();

public:
    glm::vec3 mTargetDirection{-1.0f};
    float mVisibleAngle{0.0f};
};
