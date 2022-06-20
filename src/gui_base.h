//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_GUI_BASE_H
#define GUI_GUI_BASE_H
#include "Eigen/Core"
#include "GL/glew.h"
#include "glsl_shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <string>

class GUIBase
{
  public:
    explicit GUIBase(int width = 600, int height = 600, std::string title = "OpenGL Window",
                     Eigen::Vector4f bg_color = Eigen::Vector4f{0.067f, 0.184f, 0.255f, 1.0f})
        : _width(width), _height(height), _window_title(std::move(title)), _bg_color(std::move(bg_color))
    {
        InitOpenGL();
    }
    virtual ~GUIBase() = default;

    void MainLoop();

    virtual void Render() = 0;

  protected:
    GLFWwindow *_window_id = nullptr;

    int _width = 600;
    int _height = 600;

    // background color
    Eigen::Vector4f _bg_color{0, 0, 0, 1};

    // title of window
    std::string _window_title = std::string("OpenGL Window");

  private:
    int InitOpenGL();
};

#endif // GUI_GUI_BASE_H
