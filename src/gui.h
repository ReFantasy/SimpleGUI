//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_GUI_H
#define GUI_GUI_H

#include "glsl_shader.h"
#include "gui_base.h"
#include "mesh.h"

struct Shader
{
    Shader()
    {
        mesh.BuildInShader();
        point.BuildInShader();
    }
    MeshShader mesh;
    MeshShader point;
};

class GUI : public GUIBase
{
  public:
    using GUIBase::GUIBase;

  protected:
    // 内置着色器
    Shader _shader;
};

#endif // GUI_GUI_H
