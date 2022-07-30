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
#include "glm/glm.hpp"
#include "glsl_shader.h"
#include "gui_base.h"
#include "mesh.h"
#include "memory"

/**
 * @brief 光源信息类
 */
struct Light
{
    // 光源坐标
    glm::vec3 position{1.2, 1.0, 2.0};

    // 光源属性
    glm::vec3 ambient{0.4f, 0.4f, 0.4f};
    glm::vec3 diffuse{0.5f, 0.5f, 0.5f};
    glm::vec3 specular{1.0f, 1.0f, 1.0f};
};

class GUI : public GUIBase
{
  public:
    GUI(int width = WIDTH_DEFAULT, int height = HEIGHT_DEFAULT, std::string title = WIN_NAME_DEFAULT,
        glm::vec4 bg_color = WIN_BG_COLOR_DEFAULT);

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
    void SetLight(const Light &new_light);

  protected:
    // 内置着色器
    GLSLShader _shader;

    // 相机
    Camera cam;

    // 光源位置
    Light _light; //;

  private:
    void init_light();
    std::shared_ptr<Mesh> light_obj;
    GLSLShader light_shader;
};

#endif // GUI_GUI_H
