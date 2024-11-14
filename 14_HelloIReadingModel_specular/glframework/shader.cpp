/*
 * Created 2024-10-17 16:19:49
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 */
#include "shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "check_error.h"
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    /*
        声明文件输入流
        打开文件
        声明字符串输入流
        文件输入流导入字符串输入流
        字符串输入流导入字符串
    */

    std::string vsShderSource, fsShaderSource;
    std::ifstream vsFile, fsFile;

	//保证ifstream遇到问题的时候可以抛出异常
	vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // 打开文件
        vsFile.open(vertexPath);
        fsFile.open(fragmentPath);
        // 将文件输入流中的字符串输入到sstream中
        std::stringstream vssstream, fssstream;
        vssstream << vsFile.rdbuf();
        fssstream << fsFile.rdbuf();

        // 关闭文件
        fsFile.close();
        vsFile.close();

        // 将字符串流转化到string当中
        vsShderSource  = vssstream.str();
        fsShaderSource = fssstream.str();
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << e.what() << '\n';
    }

    const char * vertexShaderSource = vsShderSource.c_str();
    const char * fragmentShaderSource = fsShaderSource.c_str();

    GLuint vs =  glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    GL_LW_CALL( glCompileShader(vs));
    checkShaderErrors(vs, "COMPILE");
    glCompileShader(fs);
    checkShaderErrors(fs, "COMPILE");

    pro =  glCreateProgram();
    glAttachShader(pro, vs);
    glAttachShader(pro, fs);

    GL_LW_CALL( glLinkProgram(pro));
    checkShaderErrors(pro, "LINK");
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
}

void Shader::begin() {
    glUseProgram(pro);
}

void Shader::end() {
    glUseProgram(0);
}

void Shader::checkShaderErrors(GLuint targert, std::string type) {
    int success = 0;
    char infoLog[1024];
    if (type == "COMPILE") {
        glGetShaderiv(targert, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(targert, 1024, NULL, infoLog);
            std::cout << "Error: SHADER COMPILE ERROR" << "\n" << infoLog << std::endl;
        }
    } else if (type == "LINK") {
        glGetProgramiv(targert, GL_LINK_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(targert, 1024, NULL, infoLog);
            std::cout << "Error: SHADER LINK ERROR" << "\n" << infoLog << "\n=====" << std::endl;
        }
    }

}

void Shader::setFloat(const std::string &attrName, float value) {
    GLuint attrLocation = glGetUniformLocation(pro, attrName.c_str());
    GL_LW_CALL(glUniform1f(attrLocation, value));
}

void Shader::setVec3(const std::string & attrName, float x, float y, float z) {
    GLuint attrLocation = glGetUniformLocation(pro, attrName.c_str());
    GL_LW_CALL(glUniform3f(attrLocation, x, y, z));
    //glUniform3fv(attrLocation, 1, new float[3]{ x, y, z });
}

void Shader::setVec3(const std::string &attrName, glm::vec3 value) {
    GLuint attrLocation = glGetUniformLocation(pro, attrName.c_str());
    GL_LW_CALL(glUniform3fv(attrLocation, 1, &value[0]));
}

void Shader::setInt(const std::string &attrName, int value) {
    GLuint attrLocation = glGetUniformLocation(pro, attrName.c_str());
    GL_LW_CALL(glUniform1i(attrLocation, value));
}

void Shader::setMat4(const std::string &attrName, const glm::mat4 &matrix) {
    GLuint attrLocation = glGetUniformLocation(pro, attrName.c_str());
    GL_LW_CALL(glUniformMatrix4fv(attrLocation, 1, GL_FALSE, glm::value_ptr(matrix)));
}

void Shader::setMat3(const std::string &attrName, const glm::mat3 &matrix) {
    GLuint attrLocation = glGetUniformLocation(pro, attrName.c_str());
    glUniformMatrix3fv(attrLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

