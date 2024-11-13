/*
 * Created 2024-10-16 14:27:16
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 */
#include "check_error.h"
#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <iostream>

void checkError() {
    std::string res = "";
    GLenum errCode = glGetError();
    //std::cout << "errCode " << errCode << std::endl;
    if (errCode != GL_NO_ERROR) {
        switch (errCode)
        {
        case GL_INVALID_ENUM:
            res = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            res = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            res = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            res = "out of memory";
            break;
        default:
            res = "unknown error";
            break;
        }
        std :: cout << res  << std::endl;
        assert(false);
    }

}