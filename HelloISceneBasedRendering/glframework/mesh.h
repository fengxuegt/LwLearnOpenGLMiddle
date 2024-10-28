#pragma once
#include "geometry.h"
#include "object.h"
#include "material/material.h"

class Mesh : public Object{
public:
    Mesh(Geometry *geometry, Material *material);
    ~Mesh();

public:
    Geometry *mGeometry{nullptr};
    Material *mMaterial{nullptr};
};
