#pragma once
#include "core.h"
#include <vector>

enum class ObjectType {
    Object,
    Mesh,
    Scene
};

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

    // 设置旋转角度
    void setAngleX(float angle);
    void setAngleY(float angle);
    void setAngleZ(float angle);


    void setScale(const glm::vec3 &scale);

    glm::mat4 getModelMatrix() const;

    Object* getParent() const;
    std::vector<Object*> getChildren() const;
    void addChild(Object *child);
    ObjectType getObjectType() const;

protected:
    glm::vec3 mPosition{0.0f};
    float mAngleX{0.0f};
    float mAngleY{0.0f};
    float mAngleZ{0.0f};
    glm::vec3 mScale{1.0f};

    // 父子关系添加代码
    std::vector<Object*> mChildren {};
    Object *mParent{nullptr};
    ObjectType mType{ObjectType::Object};


};

