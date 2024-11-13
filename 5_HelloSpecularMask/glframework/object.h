#pragma once
#include <core.h>


class Object {
public:
    Object();
    virtual ~Object();
    void setPosition(const glm::vec3 &position);
    glm::vec3 getPosition() {
        return mPosition;
    }

    // 增量旋转
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void setScale(const glm::vec3 &scale);

    glm::mat4 getModelMatrix() const;

protected:
    glm::vec3 mPosition{0.0f};
    float mAngleX{0.0f};
    float mAngleY{0.0f};
    float mAngleZ{0.0f};
    glm::vec3 mScale{1.0f};


};

