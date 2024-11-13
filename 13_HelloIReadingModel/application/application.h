#pragma once
#define lwapp Application::getInstance()
class GLFWwindow;
#include <string>

using ResizeCallback = void(*)(int, int);
using KeyBoardCallback = void (*)(int, int , int);
using MouseCallback = void (*)(int, int, int);
using CursorCallback = void (*)(double, double);
using ScrollCallback = void (*)(double);
class Application {
    public:
        static Application * getInstance();
        ~Application();
        void sayHello();

        uint32_t getWidth() const {
            return mWidth;
        }
        uint32_t getHeight() const {
            return mHeight;
        }

        bool init(const int &width = 800, const int &height = 600, const std::string windowTitle = "");
        bool update();
        void destroy();
    
        void setResizeCallback(ResizeCallback callback) {
            mResizeCallback = callback;
        }
        void setKeyBoardCallback(KeyBoardCallback callback) {
            mKeyBoardCallback = callback;
        }
        void setMouseCallback(MouseCallback callback) {
            mMouseCallback = callback;
        }
        void setCursorCallback(CursorCallback callback) {
            mCursorCallback = callback;
        }
        void setScrollCallback(ScrollCallback callback) {
            mScrollCallback = callback;
        }

        void getCursorPosition(double * x, double * y);
        GLFWwindow * getWindow() const {return mWindow;}

    private:
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) ;
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
        static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    private:
        Application();
        static Application * mInstance;
        uint32_t mWidth{0};
        uint32_t mHeight{0};
        GLFWwindow* mWindow{nullptr};
        std::string mWindowTitle{""};
        ResizeCallback mResizeCallback{nullptr};
        KeyBoardCallback mKeyBoardCallback{nullptr};
        MouseCallback mMouseCallback{nullptr};
        CursorCallback mCursorCallback{nullptr};
        ScrollCallback mScrollCallback{nullptr};
};


