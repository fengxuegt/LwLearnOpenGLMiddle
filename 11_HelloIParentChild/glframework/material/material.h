#pragma once

enum class MaterialType {
    PhongMaterial,
    WhiteMatial
};


class Material {
public:
    Material();
    virtual ~Material();

public:
    MaterialType mType;

};
