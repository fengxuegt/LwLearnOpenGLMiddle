/*
 * Created 2024-10-16 15:51:26
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 */
#include "application.h"
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>


void Application::getCursorPosition(double *x, double *y) {
    glfwGetCursorPos(mWindow, x, y);
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "framebuffer_size_callback" << std::endl;
    Application *self = (Application*) glfwGetWindowUserPointer(window);
    if (self->mResizeCallback != nullptr) {
        self->mResizeCallback(width, height); 
    }
}

// 声明一个响应键盘消息回调函数
void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // std::cout << "keyCallback" << std::endl;
    Application *self = (Application*) glfwGetWindowUserPointer(window);
    if (self->mKeyBoardCallback != nullptr) {
        self->mKeyBoardCallback(key, action, mods); 
    }
}

void Application::mouseCallback(GLFWwindow *window, int button, int action, int mods) {
    // std::cout << "mouseCallback " << button <<  std::endl;
    Application *self = (Application*) glfwGetWindowUserPointer(window);
    if (self->mMouseCallback != nullptr) {
        self->mMouseCallback(button, action, mods);
    }

}

void Application::cursorCallback(GLFWwindow *window, double xpos, double ypos) {
    // std::cout << "cursorCallback" << std::endl;
    Application *self = (Application*) glfwGetWindowUserPointer(window);
    if (self->mCursorCallback != nullptr) {
        self->mCursorCallback(xpos, ypos);
    }

}

void Application::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    std::cout << "scrollCallback" << std::endl;
    Application *self = (Application*) glfwGetWindowUserPointer(window);
    if (self->mScrollCallback != nullptr) {
        self->mScrollCallback(yoffset);
    }
}


bool Application::init(const int &width, const int &height, const std::string windowTitle) {
    mWindowTitle = windowTitle;
    mWidth = width;
    mHeight = height;
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // 设置 GLFW 版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    mWindow = glfwCreateWindow(width, height, mWindowTitle.c_str(), NULL, NULL);
    if (mWindow == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(mWindow);

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // 注意这里才是真正设置回调函数的地方，前面的代码都是把回调函数保存起来

    // 注册窗口大小回调
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    //this就是当前全局唯一的Application对象
	glfwSetWindowUserPointer(mWindow, this);
    glfwSetKeyCallback(mWindow, keyCallback);
    glfwSetMouseButtonCallback(mWindow, mouseCallback);
    glfwSetCursorPosCallback(mWindow, cursorCallback);
    glfwSetScrollCallback(mWindow, scrollCallback);
    return true;
}
bool Application::update(){
    if (glfwWindowShouldClose(mWindow)) {
        return false;
    }

    // 交换缓冲区
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
    return true;
}
void Application::destroy(){
    glfwTerminate();
}



void Application::sayHello() {
    std :: cout << "hello" << std::endl;
}
Application * Application::mInstance = nullptr;
Application * Application::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new Application();
    }
    return mInstance;
}


Application::~Application() {
    std::cout << "~Application()" << std::endl;
}

Application::Application() {

}
