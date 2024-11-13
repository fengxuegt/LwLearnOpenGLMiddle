//
// Created by 心心旺旺 on 2024/10/28.
//

#include "util.h"

void Util::decompose(glm::mat4 &matrix, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale) {
    glm::quat quaternion;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(matrix, scale, quaternion, position, skew, perspective);

    // 四元数--欧拉角
    glm::mat4 rotationMatrix = glm::toMat4(quaternion);
    glm::extractEulerAngleXYZ(rotationMatrix, rotation.x, rotation.y, rotation.z);
    rotation.x = glm::degrees(rotation.x);
    rotation.y = glm::degrees(rotation.y);
    rotation.z = glm::degrees(rotation.z);

}
