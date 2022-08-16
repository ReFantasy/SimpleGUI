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
#include "Scene.h"





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
