//
// Created by 心心旺旺 on 2024/10/21.
//

#include "texture.h"

#include <iostream>
#include <ostream>

#include "../application/stb_image.h"

std::map<std::string, Texture * > Texture::mTextureCache{};
Texture * Texture::createTexture(const std::string &filepath, unsigned int unit) {
    // 检查是否缓存过纹理
    auto iter = mTextureCache.find(filepath);
    if (iter == mTextureCache.end()) {
        return iter->second;
    }
    // 如果没有生成过，则直接生成
    auto texture = new Texture(filepath, unit);
    mTextureCache[filepath] = texture;
    return texture;
}

Texture * Texture::createTexture(const std::string &filepath, unsigned int unit, unsigned char *data, int height,
    int width) {
    // 检查是否缓存过纹理
    auto iter = mTextureCache.find(filepath);
    if (iter == mTextureCache.end()) {
        return iter->second;
    }
    // 如果没有生成过，则直接生成
    auto texture = new Texture(data, unit, width, height);
    mTextureCache[filepath] = texture;
    return texture;
}

Texture::Texture(const std::string &filePath, int texture) {
    mUnit = texture;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filePath.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Failed to load image: " << filePath << std::endl;
    }
    glGenTextures(1, &mTexture);
    glActiveTexture(GL_TEXTURE0 + texture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//4 设置纹理的过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//5 设置纹理的包裹方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v
	stbi_image_free(data);
}

Texture::Texture(unsigned char *memory, unsigned int unit, int width, int height) {
    mUnit = unit;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    // 计算整张图片的大小
    // 如果内嵌纹理是png或者是jpg压缩格式的话，height = 0；width就代表了整张图片的大小
    unsigned int dataSize = 0;
    if (!height) {
        dataSize = width;
    } else {
        // 统一认为数据格式都是RGBA
        dataSize = width * height * 4;
    }

    unsigned char *data = stbi_load_from_memory(memory, dataSize, &mWidth, &mHeight, &channels, STBI_rgb_alpha);
    glGenTextures(1, &mTexture);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //4 设置纹理的过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //5 设置纹理的包裹方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v
    stbi_image_free(data);
}

Texture::~Texture() {
    if (mTexture != 0) {
        glDeleteTextures(1, &mTexture);
    }
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + mUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}

void Texture::setUnit(unsigned int unit) {
    mUnit = unit;
}
