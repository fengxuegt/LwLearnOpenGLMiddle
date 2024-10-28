#pragma once
#include "core.h"
#include <string>
class Texture {
public:
    Texture(const std::string &filePath, int texture);
    ~Texture();
    void bind() const;

private:
    unsigned int mTexture {0}; // 纹理的ID
    int mWidth{0}; // 纹理宽度
    int mHeight{0}; // 纹理高度
    unsigned int mUnit{0}; // 纹理单元值
};



