//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_GUI_H
#define GUI_GUI_H

#include "camera.h"
#include "glsl_shader.h"
#include "gui_base.h"
#include "mesh.h"

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

  protected:
    // 内置着色器
    GLSLShader _shader;

    // 相机
    Camera cam;
};

#endif // GUI_GUI_H
