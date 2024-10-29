#pragma once
#include <map>

#include "core.h"
#include <string>
class Texture {
public:
    static Texture * createTexture(const std::string &filepath, unsigned int unit);
    static Texture * createTexture(const std::string &filepath, unsigned int unit, unsigned char *data, int height,int width);
    Texture(const std::string &filePath, int texture);
    Texture(unsigned char *data, unsigned int unit,int width, int height);
    ~Texture();
    void bind() const;
    void setUnit(unsigned int unit);

private:
    unsigned int mTexture {0}; // 纹理的ID
    int mWidth{0}; // 纹理宽度
    int mHeight{0}; // 纹理高度
    unsigned int mUnit{0}; // 纹理单元值

    static std::map<std::string, Texture * > mTextureCache;
};



