/*
 * Created 2024-10-16 09:32:14
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 */

#include "core.h"
#include "check_error.h"
#include "application.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION  // 这个地方定义了一个宏，如果不定义的话会报错，但是不知道什么原因
#include <iostream>
#include <ostream>

#include "gamecameracontrol.h"
#include "geometry.h"
#include "perspectiveCamera.h"
#include "stb_image.h"
#include "texture.h"
#include "trackballcameracontrol.h"

#include "camera/camera.h"
#include "camera/cameracontrol.h"

Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;
Geometry *geometry = nullptr;

GLuint pro;
GLuint texture1, texture2;
Shader* shader = nullptr;
glm::mat4 orthographicMatrix(1.0f);
glm::mat4 perspectiveMatrix(1.0f);
//平行光：参数（方向，光强） uniform变量形式
glm::vec3 lightDirection = glm::vec3(-1.0f, 0.0f, -1.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
float lightIntensity = 0.5f;
glm::vec3 ambientColor = glm::vec3(0.2f, 0.3f, 0.2f);
glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

void onResize(int width, int height);
void OnKey(int key, int action, int mods);
void OnMouse(int button, int action, int mods);
void OnCursor(double x, double y);
void OnScroll(double y);

void prepareTexture() {
    Texture* textureObj1 = new Texture("assets/textures/earth.png", 0);
    Texture* textureObj2 = new Texture("assets/textures/earth.png", 1);
}

void prepareShaderClass() {

    shader = new Shader("assets/shaders/vertex.glsl","assets/shaders/fragment.glsl");
}

void render() {
    // 渲染指令
    GL_LW_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    shader->begin();
    shader->setFloat("time", glfwGetTime());

    shader->setVec3("uniColor", 0.5f, 0.5f, 0.5f);
    shader->setInt("texture1",0);
    shader->setInt("texture2",1);
    shader->setMat4("transform", transform);

    // viewMatrix
    shader->setMat4("viewMatrix", camera->getViewMatrix());

    // orthographicMatrix
    shader->setMat4("orthographicMatrix", orthographicMatrix);

    // perspectiveMatrix
    shader->setMat4("perspectiveMatrix", camera->getProjectionMatrix());

    //光源参数的uniform更新
	shader->setVec3("lightDirection", lightDirection);
	shader->setVec3("lightColor", lightColor);
    shader->setFloat("lightIntensity", lightIntensity);
    shader->setVec3("ambientColor", ambientColor);
    shader->setVec3("cameraPosition", camera->mPosition);

    GL_LW_CALL(glBindVertexArray(geometry->getVAO()));
    GL_LW_CALL(glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0));
    GL_LW_CALL(glBindVertexArray(0));
    
    shader->end();
}

void doTransform() {
    transform = glm::rotate(transform, 0.005f, glm::vec3(0.0f, 1.0f, 1.0f));
}

void prepareCamera() {
    // lookat函数：生成一个matrix矩阵
    // 参数说明：
    /*
     *eye : 摄像机所在的位置
     *center： 当摄像机看向的那个点
     *up：穹顶向量
     */

    // 透视投影相机
    camera = new PerspectiveCamera(
        60.0f,
        (float)lwapp->getWidth() / (float)lwapp->getHeight(),
        0.1f,
        1000.0f
    );

    // 正交投影相机
    // float size = 6.0f;
    // camera = new OrthographicCamera(-size, size, size, -size, size, -size);

    cameraControl = new TrackBallCameraControl();
    // cameraControl = new GameCameraControl();
    cameraControl->setCamera(camera);
}


void prepareVAO() {
    // geometry = Geometry::createBox(3.0f);
    geometry = Geometry::createSphere(3.0f);
    // geometry = Geometry::createPlane(3.0f, 2.0f);
}

void prepareState() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

int main() {
    if (!lwapp->init(800, 600, "HelloSpecular")) {
        return -1;
    }
    // 设置回调函数
    lwapp->setResizeCallback(onResize);
    lwapp->setKeyBoardCallback(OnKey);
    lwapp->setMouseCallback(OnMouse);
    lwapp->setCursorCallback(OnCursor);
    lwapp->setScrollCallback(OnScroll);

    GL_LW_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0));

    prepareVAO();
    prepareTexture();
    prepareShaderClass();
    prepareCamera();
    prepareState();
    
    // 主循环
    while (lwapp->update()) {
        doTransform();
        cameraControl->update();
        render();
    }
    lwapp->destroy();
    
    return 0;
}

void onResize(int width, int height) {
    GL_LW_CALL(glViewport(0, 0, width, height));

}

void OnKey(int key, int action, int mods) {
    cameraControl->onKey(key, action, mods);
}
void OnMouse(int button, int action, int mods) {
    // if (action == GLFW_PRESS) {
    //     if (button == GLFW_MOUSE_BUTTON_LEFT) {
    //         std::cout << "Mouse Left Down" << std::endl;
    //     } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    //         std::cout << "Mouse Right Down" << std::endl;
    //     } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
    //         std::cout << "Mouse Middle Down" << std::endl;
    //     }
    // }
    double x, y;
    lwapp->getCursorPosition(&x, &y);
    cameraControl->onMouse(button, action, x, y);
}

void OnCursor(double x, double y) {
    cameraControl->onCursor(x, y);
}

void OnScroll(double y) {
    cameraControl->onScroll(y);
}