#pragma once
#include <glm/vec3.hpp>


class Light {
public:
    Light();
    virtual ~Light();

public:
    glm::vec3 mColor{1.0f};
    float mSpecularIntensity{1.0f};
};
