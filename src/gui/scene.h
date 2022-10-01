//
// Created by ReFantasy on 2022/8/17.
//

#ifndef GUI_SCENE_H
#define GUI_SCENE_H
#include "camera.h"
#include <memory>

class Mesh;
class GLSLShader;
/* 光源属性 */
struct Light
{
    // 光源坐标
    glm::vec3 position{1.2, 1.0, 2.0};

    // 光源颜色
    glm::vec3 ambient{0.4f, 0.4f, 0.4f};
    glm::vec3 diffuse{0.5f, 0.5f, 0.5f};
    glm::vec3 specular{1.0f, 1.0f, 1.0f};
};

/*
 * 场景类定义了点光源和相机
 */
class Scene
{
    friend class GUI;
    friend class Sphere2;

public:
    Scene();

    Light &GetLight()
    {
        return _light;
    }

    Camera &GetCamera()
    {
        return _cam;
    }

private:
    /* 相机 */
    Camera _cam;

    /* 光源 */
    Light _light;
    std::shared_ptr<Mesh> light_obj;
    std::shared_ptr<GLSLShader> light_shader;
    void init_light();

private:
    void Render(int win_width, int win_height);
};

#endif // GUI_SCENE_H
