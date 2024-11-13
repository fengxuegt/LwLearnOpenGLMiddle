#pragma once
#include "light.h"

class Directionallight : public Light{
public:
    Directionallight();
    virtual ~Directionallight();

public:
    glm::vec3 mDirection{-1.0f};
};
