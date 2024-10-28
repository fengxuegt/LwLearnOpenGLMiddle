/*
 * Created 2024-10-17 16:19:42
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 */
#pragma once
#include "core.h"
#include <string>
class Shader
{

private:
    GLuint pro{0};
    void checkShaderErrors(GLuint targert, std::string type);
    
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();
    void begin(); // 开始使用当前Shader
    void end(); // 停止使用当前Shader
    void setFloat(const std::string &attrName, float value);
    void setVec3(const std::string & attrName, float x, float y, float z);
    void setVec3(const std::string & attrName, glm::vec3 value);
    void setInt(const std::string &attrName, int value);
    void setMat4(const std::string &attrName, const glm::mat4 &matrix);
    void setMat3(const std::string &attrName, const glm::mat3 &matrix);

    // void setVect3(const std::string &attrName, )
};



