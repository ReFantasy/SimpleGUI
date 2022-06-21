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
    _shader.setMat4("model", glm::mat4(1));
    _shader.setMat4("view", cam.GetViewMatrix());
    _shader.setMat4("projection", cam.GetPerspectiveMatrix((float)width / (float)height));

    _shader.setVec3("viewPos", cam.GetCameraPosition());

    _shader.setVec3("light.position", _light.position);
    _shader.setVec3("light.ambient", _light.ambient);
    _shader.setVec3("light.diffuse", _light.diffuse);
    _shader.setVec3("light.specular", _light.specular);

    _shader.deactivate();

    // 用户渲染
    Render();
}

