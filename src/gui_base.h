//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_GUI_BASE_H
#define GUI_GUI_BASE_H
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <iostream>
#include <memory>
#include <string>

// 窗口默认宽度
#define WIDTH_DEFAULT 512
// 默认窗口高度
#define HEIGHT_DEFAULT 512
// 窗口默认名称
#define WIN_NAME_DEFAULT "OpenGL Window"
// 窗口默认背景颜色
#define WIN_BG_COLOR_DEFAULT                                                                                           \
    {                                                                                                                  \
        0.067f, 0.184f, 0.255f, 1.0f                                                                                   \
    }

class GUIBase
{
  public:
    explicit GUIBase(int width = WIDTH_DEFAULT, int height = HEIGHT_DEFAULT, std::string title = WIN_NAME_DEFAULT,
                     glm::vec4 bg_color = WIN_BG_COLOR_DEFAULT)
        : _width(width), _height(height), _window_title(std::move(title)), _bg_color(bg_color)
    {
        InitOpenGL();
    }
    virtual ~GUIBase() = default;

    void MainLoop();

    virtual void Render() = 0;

  protected:
    GLFWwindow *_window_id = nullptr;

    int _width = WIDTH_DEFAULT;
    int _height = HEIGHT_DEFAULT;

    // background color
    glm::vec4 _bg_color{};

    // title of window
    std::string _window_title = std::string("OpenGL Window");

  private:
    int InitOpenGL();
};

#endif // GUI_GUI_BASE_H
