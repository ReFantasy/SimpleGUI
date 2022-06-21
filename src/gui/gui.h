/*
 * Created by refantasy on 2022/6/20.
 *
 * 图形界面类，处理相机及着色器
 * 通过继承该类并重载 void Render() 函数，实现自定义对象的渲染
 *
 */

#ifndef GUI_GUI_H
#define GUI_GUI_H

#include "camera.h"
#include "glsl_shader.h"
#include "gui_base.h"
#include "mesh.h"
#include "glm/glm.hpp"

struct Light
{
    glm::vec3 position {1.2,1.0,2.0};
    glm::vec3 ambient  { 0.2f, 0.2f, 0.2f};
    glm::vec3 diffuse  {0.5f, 0.5f, 0.5f};
    glm::vec3 specular {1.0f, 1.0f, 1.0f};
};

class GUI : public GUIBase
{
  public:
    using GUIBase::GUIBase;

    void BaseRender() override;



    virtual void Render() = 0;

    Camera &GetCamera()
    {
        return cam;
    }
    GLSLShader &GetShader()
    {
        return _shader;
    }
    Light& GetLight()
    {
        return _light;
    }

  protected:
    // 内置着色器
    GLSLShader _shader;

    // 相机
    Camera cam;

    // 光源位置
    Light _light;//;
};

#endif // GUI_GUI_H
