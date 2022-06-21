//
// Created by refantasy on 2022/6/20.
//

#include "gui.h"
void GUI::BaseRender()
{
    // 计算投影矩阵并传递给着色器
    int width, height;
    glfwGetWindowSize(_window_id, &width, &height);
    _shader.activate();
    auto mvp = cam.GetPerspectiveMatrix((float)width / (float)height) * cam.GetViewMatrix();
    _shader.setMat4("MVP", mvp);
    _shader.deactivate();

    // 用户渲染
    Render();
}
