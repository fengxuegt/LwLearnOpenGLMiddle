#pragma once

enum class MaterialType {
    PhongMaterial
};


class Material {
public:
    Material();
    virtual ~Material();

public:
    MaterialType mType;

};
