#pragma once
#include "material.h"
#include "texture.h"

class Phonematerial : public Material{
public:
    Phonematerial();
    ~Phonematerial();
public:
    Texture* mDiffuse{nullptr};
    float mShininess{1.0};

};
