
# ������̬�� (��̬�⣬�����Ҫ)
add_library(application STATIC application.cpp
        camera/camera.cpp
        camera/orthographicCamera.cpp
        camera/perspectiveCamera.cpp
        camera/cameracontrol.cpp
        camera/trackballcameracontrol.cpp
        camera/gamecameracontrol.cpp
        camera/gamecameracontrol.h
        assimploader.cpp
        assimploader.h)

# �� application Ŀ¼��ͷ�ļ�·������Ϊ PUBLIC��ʹ����ĿҲ���Է���
target_include_directories(application PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/camera
)
