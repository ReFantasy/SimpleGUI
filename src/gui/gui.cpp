//
// Created by refantasy on 2022/6/20.
//

#include "gui.h"
#include <vector>

#include <utility>
GUI::GUI(int width, int height, std::string title, glm::vec4 bg_color)
    : GUIBase(width, height, std::move(title), bg_color)
{
    init_light();
}

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

    // 绘制光源对象
    light_shader.activate();
    light_shader.setVec3("light_position", _light.position);
    light_shader.setVec3("light_color", _light.diffuse + _light.ambient);
    light_shader.setMat4("model", glm::mat4(1));
    light_shader.setMat4("view", cam.GetViewMatrix());
    light_shader.setMat4("projection", cam.GetPerspectiveMatrix((float)width / (float)height));
    light_shader.deactivate();

    light_obj->Draw(light_shader.GetShaderID());

    // 用户渲染
    Render();
}
void GUI::SetLight(const Light &new_light)
{
    _light = new_light;
    _shader.activate();
    _shader.setVec3("light.position", _light.position);
    _shader.setVec3("light.ambient", _light.ambient);
    _shader.setVec3("light.diffuse", _light.diffuse);
    _shader.setVec3("light.specular", _light.specular);
    _shader.deactivate();
}
void GUI::init_light()
{
    /**
     * 创建一个光源
     */
    float vertices[] = {// positions          // normals           // texture coords
                        -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
                        0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

                        -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
                        0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

                        -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

                        0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
                        0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

                        -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
                        0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

                        -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
                        0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f};

    std::vector<Vertex> light_vertex;
    std::vector<unsigned int> light_indices;
    for (int i = 0; i < 36; i++)
    {
        Vertex v;
        int base = 3 * i;
        float scale = 0.2;
        v.Position = glm::vec3(vertices[base + 0] * scale, vertices[base + 1] * scale, vertices[base + 2] * scale);
        v.Color = glm::vec3(1, 1, 1);
        light_vertex.push_back(v);
        light_indices.push_back(i);
    }
    light_obj = std::make_shared<Mesh>(light_vertex, light_indices);
    light_obj->GenGLBuffers();

    const char vs[] = R"(
                            #version 410 core
                            layout (location = 0) in vec3 aPos;

                            uniform vec3 light_position;
                            uniform mat4 model;
                            uniform mat4 view;
                            uniform mat4 projection;

                            void main()
                            {
                                gl_Position = projection * view * model * vec4(aPos+light_position, 1.0);
                            }
                        )";
    const char fs[] = R"(
                            #version 410 core
                            out vec4 FragColor;
                            uniform vec3 light_color;

                            void main()
                            {
                                FragColor = vec4(light_color, 1.0); // set alle 4 vector values to 1.0
                            }
                        )";
    light_shader.LoadShaderFromString(vs, fs, "");
}
