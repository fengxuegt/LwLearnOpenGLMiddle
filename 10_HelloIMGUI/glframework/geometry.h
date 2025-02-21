#pragma once
#include <glad/glad.h>

class Geometry {
public:
    Geometry();
    ~Geometry();

    static Geometry* createBox(float size); // 创建盒子
    static Geometry* createSphere(float radius); // 创建球体
    static Geometry* createPlane(float width, float height);

    GLuint getVAO() const;
    GLuint getIndicesCount() const;


private:
    GLuint mVao{0};
    GLuint mPosVbo{0};
    GLuint mUvVbo{0};
    GLuint mEbo{0};
    GLuint mNormalVbo{ 0 };

    unsigned int mIndicesCount{0};
};

