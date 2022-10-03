/*
 *
 * 用户界面类，处理相机及着色器
 * 通过继承该类并重载 void Render() 函数，实现自定义对象的渲染
 *
 */

#ifndef __GUI_H__
#define __GUI_H__

#include "GLFW/glfw3.h"
#include "gui_base.h"
#include "memory"

/**
 * 用户自定义界面类
 * 通过重载机制，在 void Render() 函数中进行对象的渲染
 *
 */
class GUI : public GUIBase
{
  public:
    using GUIBase::GUIBase;
    virtual ~GUI() = default;

    virtual void Render(){};

  private:
    /**
     * 纯虚函数，重载执行渲染任务
     */
    virtual void BaseRender() final
    {
        /* 获取当前窗口宽和高*/
        int width, height;
        glfwGetWindowSize(_window_id, &width, &height);

        /* 用户渲染 */
        Render();
    }
};

#endif // __GUI_H__