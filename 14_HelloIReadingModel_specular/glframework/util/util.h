#pragma once
#include "../glframework/core.h"

class Util {
public:
    // 传入矩阵，解析位置、旋转和缩放信息
    static void decompose(glm::mat4 &matrix, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale);
};
