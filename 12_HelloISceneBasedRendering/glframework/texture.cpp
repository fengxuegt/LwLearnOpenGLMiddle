//
// Created by 心心旺旺 on 2024/10/21.
//

#include "texture.h"

#include <iostream>
#include <ostream>

#include "../application/stb_image.h"


Texture::Texture(const std::string &filePath, int texture) {
    std::cout << "Loading texture " << filePath << std::endl;
    mUnit = texture;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filePath.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);
    std::cout<<data<<std::endl;
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

Texture::~Texture() {
    if (mTexture != 0) {
        glDeleteTextures(1, &mTexture);
    }
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + mUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}
