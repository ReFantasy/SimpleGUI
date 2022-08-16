//
// Created by ReFantasy on 2022/8/17.
//

#include "scene.h"

void Scene::init_light()
{
    /**
     * 光源顶点属性数组
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
        int base    = 3 * i;
        float scale = 0.2;
        v.Position  = glm::vec3(vertices[base + 0] * scale, vertices[base + 1] * scale, vertices[base + 2] * scale);
        v.Color     = glm::vec3(1, 1, 1);
        light_vertex.push_back(v);
        light_indices.push_back(i);
    }

    /* 创建光源对象 */
    light_obj = std::make_shared<Mesh>(light_vertex, light_indices);
    light_obj->GenGLBuffers();

    /* 光源着色器*/
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
void Scene::Render(int width, int height)
{
    // 绘制光源对象
    light_shader.activate();
    light_shader.setVec3("light_position", _light.position);
    light_shader.setVec3("light_color", _light.diffuse + _light.ambient);
    light_shader.setMat4("model", glm::mat4(1));
    light_shader.setMat4("view", _cam.GetViewMatrix());
    light_shader.setMat4("projection", _cam.GetPerspectiveMatrix((float)width / (float)height));
    light_shader.deactivate();

    if (light_obj) light_obj->Draw(light_shader.GetShaderID());
}
