#pragma once
#include "material.h"
#include "../glframework/texture.h"

class Phonematerial : public Material{
public:
    Phonematerial();
    ~Phonematerial();
public:
    Texture* mDiffuse{nullptr};
    Texture* mSpecularMask{nullptr};
    float mShininess{0.1};

};
