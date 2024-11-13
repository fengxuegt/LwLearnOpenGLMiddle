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
#include "mesh.h"
#include "perspectiveCamera.h"
#include "stb_image.h"
#include "texture.h"
#include "trackballcameracontrol.h"

#include "camera/camera.h"
#include "camera/cameracontrol.h"
#include "light/pointlight.h"
#include "material/phonematerial.h"
#include "material/whitematerial.h"
#include "renderer/renderer.h"

Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;
Geometry *geometry = nullptr;

Renderer *renderer = nullptr;
std::vector<Mesh *> meshes{};
Directionallight *directionalLight = nullptr;
PointLight *pointLight = nullptr;
SpotLight *spotLight = nullptr;
Ambientlight *ambientLight = nullptr;

void onResize(int width, int height);
void OnKey(int key, int action, int mods);
void OnMouse(int button, int action, int mods);
void OnCursor(double x, double y);
void OnScroll(double y);

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

void prepare() {
    // 创建Geometry
    auto box = Geometry::createBox(3.0f);
    // 创建Material材质
    auto material01 = new Phonematerial();
    material01->mShininess = 32.0f;
    material01->mDiffuse = new Texture("assets/textures/box.png", 0);
    material01->mSpecularMask = new Texture("assets/textures/sp_mask.png", 1);
    // 创建mesh
    auto mesh01 = new Mesh(box, material01);
    meshes.push_back(mesh01);

    // 创建光源
    auto lightBall = Geometry::createSphere(0.5f);
    auto material02 = new WhiteMaterial();
    auto mesh02 = new Mesh(lightBall, material02);
    mesh02->setPosition(glm::vec3(0.0f, 0, 3));
    meshes.push_back(mesh02);

    pointLight = new PointLight();
    pointLight->setPosition(mesh02->getPosition());
    pointLight->mK2 = 0.017f;
    pointLight->mK1 = 0.07f;
    pointLight->mKc = 1.0f;

    spotLight = new SpotLight();
    spotLight->setPosition(mesh02->getPosition());
    spotLight->mVisibleAngle = 30.0f;
    spotLight->mTargetDirection = glm::vec3(0.0f, 0.0f, -1.0f);


    directionalLight = new Directionallight();
    ambientLight = new Ambientlight();
    ambientLight->mColor = glm::vec3(0.1f, 0.1f, 0.1f);
    renderer = new Renderer();
}

void lightTransformRotate() {
    float time = glfwGetTime();
    auto poz = pointLight->getPosition().z;
    std::cout << poz << std::endl;
    meshes[1]->setPosition(glm::vec3(-10 * sin(time), 0, 10 * cos(time)));
    pointLight->setPosition(glm::vec3(-10 * sin(time), 0, 10 * cos(time)));
}

void lightTransformTranslate() {
	float xPos = glm::sin(glfwGetTime()) + 3.0f;
	meshes[1]->setPosition(glm::vec3(0.0f, 0.0f, xPos));
	pointLight->setPosition(glm::vec3(0.0f, 0.0f, xPos));
    spotLight->setPosition(glm::vec3(0.0f, 0.0f, xPos));
}

int main() {
    if (!lwapp->init(800, 600, "HelloSpotLight")) {
        return -1;
    }
    // 设置回调函数
    lwapp->setResizeCallback(onResize);
    lwapp->setKeyBoardCallback(OnKey);
    lwapp->setMouseCallback(OnMouse);
    lwapp->setCursorCallback(OnCursor);
    lwapp->setScrollCallback(OnScroll);

    GL_LW_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0));
    prepareCamera();
    prepare();
    
    // 主循环
    while (lwapp->update()) {
        // lightTransformRotate(); // 绕箱子旋转
        lightTransformTranslate();
        cameraControl->update();
        // renderer->render(meshes, camera, directionalLight, ambientLight);
        renderer->render(meshes, camera, spotLight, ambientLight);
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