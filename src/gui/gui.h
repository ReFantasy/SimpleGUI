/*
 *
 * 用户界面类，处理相机及着色器
 * 通过继承该类并重载 void Render() 函数，实现自定义对象的渲染
 *
 */

#ifndef __GUI_H__
#define __GUI_H__

#include "camera.h"
#include "glsl_shader.h"
#include "gui_base.h"
#include "memory"
#include "mesh.h"

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

  public:
    Scene()
    {
        init_light();
    }

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
    GLSLShader light_shader;
    void init_light();

  private:
    void Render(int win_width, int win_height);
};

/**
 * 用户自定义界面类
 * 通过重载机制，在 void Render() 函数中进行对象的渲染
 *
 */
class GUI : public GUIBase
{
  public:
    using GUIBase::GUIBase;

    /**
     * 重载函数，执行具体的渲染任务
     */
    virtual void Render() = 0;

    /* 场景: 相机 光源 */
    Scene scene;

    /* 着色器 */
    GLSLShader _shader;

  private:
    void BaseRender() final;
};

#endif // __GUI_H__
