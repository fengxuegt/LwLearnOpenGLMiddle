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
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <iostream>
#include <ostream>
#include <assimp/anim.h>

#include "assimploader.h"
#include "imgui.h"

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
#include "assimploader.h"

Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;
Geometry *geometry = nullptr;

Renderer *renderer = nullptr;
Scene *scene = nullptr;
Directionallight *directionalLight = nullptr;
PointLight *pointLight = nullptr;
SpotLight *spotLight = nullptr;
Ambientlight *ambientLight = nullptr;

glm::vec3 clearColor{};

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
    scene = new Scene();
    // auto test = AssimpLoader::loadFromFile("assets/fbx/Fist Fight B.fbx");
    auto test = AssimpLoader::loadFromFile("assets/fbx/bag/backpack.obj");
    scene->addChild(test);
    scene->setScale(glm::vec3(0.5f, 0.5f, 0.5f));

    directionalLight = new Directionallight();
    directionalLight->mDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    directionalLight->mSpecularIntensity = 0.2f;
    ambientLight = new Ambientlight();
    ambientLight->mColor = glm::vec3(0.5f, 0.5f, 0.5f);
    renderer = new Renderer();
}



void initImageui() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(lwapp->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

}

void renderIMGUI() {
    // 开启当前的IMGUI渲染
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 决定当前的GUI上面有哪些控件，从上到下
    ImGui::Begin("Hello IMGUI");
    ImGui::Text("Change backgrond color.");
    ImGui::Button("Rotate", ImVec2(60, 20));
    ImGui::ColorEdit3("Clear color", (float*)&clearColor);


    ImGui::End();

    // 执行渲染
    ImGui::Render();
    int display_w, display_h;
    // 获取当前窗体的宽和高
    glfwGetFramebufferSize(lwapp->getWindow(), &display_w, &display_h);
    // std::cout << display_w << " " << display_h << std::endl;
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

int main() {
    if (!lwapp->init(800, 600, "HelloReadingModel")) {
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
    initImageui();
    
    // 主循环
    while (lwapp->update()) {
        // lightTransformRotate(); // 绕箱子旋转
        // lightTransformTranslate();

        cameraControl->update();
        // renderer->render(meshes, camera, directionalLight, ambientLight);
        renderer->setClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);
        renderer->render(scene, camera, directionalLight, ambientLight);
        renderIMGUI();
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