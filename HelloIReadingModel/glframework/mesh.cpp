//
// Created by 心心旺旺 on 2024/10/24.
//

#include "mesh.h"

Mesh::Mesh(Geometry *geometry, Material *material) {
    mGeometry = geometry;
    mMaterial = material;
    mType = ObjectType::Mesh;
}

Mesh::~Mesh() {
}
