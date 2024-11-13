//
// Created by 心心旺旺 on 2024/10/24.
//

#include "object.h"

Object::Object() {
}

Object::~Object() {
}

void Object::setPosition(const glm::vec3 &position) {
    mPosition = position;
}

void Object::rotateX(float angle) {
    mAngleX += angle;
}

void Object::rotateY(float angle) {
    mAngleY += angle;
}

void Object::rotateZ(float angle) {
    mAngleZ += angle;
}

void Object::setAngleX(float angle) {
    mAngleX = angle;
}

void Object::setAngleY(float angle) {
    mAngleY = angle;
}

void Object::setAngleZ(float angle) {
    mAngleZ = angle;
}

void Object::setScale(const glm::vec3 &scale) {
    mScale = scale;
}

glm::mat4 Object::getModelMatrix() const {
    // 父亲的变换矩阵
    glm::mat4 parentModelMatrix = glm::mat4(1.0f);
    if (mParent != nullptr) {
        parentModelMatrix = mParent->getModelMatrix();
    }

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    // 缩放矩阵
    modelMatrix = glm::scale(modelMatrix, mScale);
    // 旋转矩阵
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    // 尝试旋转起来
    // modelMatrix = glm::rotate(modelMatrix, 0.03f, glm::vec3(0.0f, 1.0f, 1.0f));

    modelMatrix = parentModelMatrix * glm::translate(glm::mat4(1.0f), mPosition) * modelMatrix;
    return modelMatrix;
}

Object * Object::getParent() const {
    return mParent;
}

std::vector<Object *> Object::getChildren() const {
    return mChildren;
}

void Object::addChild(Object *child) {
    auto iter = std::find(mChildren.begin(), mChildren.end(), child);
    if (iter == mChildren.end()) {
        mChildren.push_back(child);
    }
    child->mParent = this;
}

ObjectType Object::getObjectType() const {
    return mType;
}
