//
// Created by ReFantasy on 2022/8/18.
//

#ifndef GUI_LINE_H
#define GUI_LINE_H
#include "vector"
#include "memory"
#include "glm/glm.hpp"
#include "Scene.h"

class GLSLShader;
class GLFWwindow;

class Line
{
public:
    explicit Line(std::vector<glm::vec3> points, std::vector<glm::vec3> color);
    bool GenGLBuffers();
    void SetSceneInfo(GLFWwindow *window_id, Scene &scene);
    void Draw(unsigned int type = 0x0001);

private:
    std::vector<glm::vec3> _points;
    std::vector<glm::vec3> _color;

    unsigned int VAO = 0, VBO = 0, EBO = 0;
    unsigned int instance_pos_vbo;
    unsigned int instance_color_vbo;

    std::shared_ptr<GLSLShader> line_shader_ptr;
};

#endif // GUI_LINE_H
