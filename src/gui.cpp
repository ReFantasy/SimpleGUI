//
// Created by refantasy on 2022/6/20.
//

#include "gui.h"
void GUI::BaseRender()
{
    int width, height;
    glfwGetWindowSize(_window_id, &width, &height);

    _shader.activate();
    auto mvp = cam.GetPerspectiveMatrix((float)width / (float)height) * cam.GetViewMatrix();
    _shader.setMat4("MVP", mvp);
    _shader.deactivate();

    Render();
}
