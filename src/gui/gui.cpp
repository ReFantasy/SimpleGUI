//
// Created by refantasy on 2022/6/20.
//

#include "gui.h"
#include "camera.h"
#include <vector>
#include "glsl_shader.h"
#include "scene.h"
#include "GLFW/glfw3.h"



void GUI::BaseRender()
{
    /* 获取当前窗口宽和高*/
    int width, height;
    glfwGetWindowSize(_window_id, &width, &height);

    /* 绘制光源对象 */
    scene->Render(width, height);

    /* 将相机和光源信息传递给着色器 */
    _shader->activate();
    _shader->setVec3("viewPos", scene->GetCamera().GetCameraPosition());

    _shader->setMat4("model", glm::mat4(1));
    _shader->setMat4("view", scene->GetCamera().GetViewMatrix());
    _shader->setMat4("projection", scene->GetCamera().GetPerspectiveMatrix((float)width / (float)height));

    _shader->setVec3("light.position", scene->GetLight().position);
    _shader->setVec3("light.ambient", scene->GetLight().ambient);
    _shader->setVec3("light.diffuse", scene->GetLight().diffuse);
    _shader->setVec3("light.specular", scene->GetLight().specular);
    _shader->deactivate();

    /* 用户渲染 */
    Render();
}
GUI::GUI(int width, int height, std::string title, glm::vec4 bg_color) : GUIBase(width, height, title, bg_color)
{
    if(!_shader)
    {
        _shader = std::make_shared<GLSLShader>();
    }
    if(!scene)
    {
        scene = std::make_shared<Scene>();
    }
}
