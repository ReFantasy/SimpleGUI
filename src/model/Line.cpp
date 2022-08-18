//
// Created by ReFantasy on 2022/8/18.
//

#include "Line.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glsl_shader.h"

Line::Line(std::vector<glm::vec3> points, std::vector<glm::vec3> color) : _points(points), _color(color)
{
    // 球的着色器
    std::string vs = R"(
		#version 410 core
        layout(location = 0) in vec3 _position;
		layout(location = 1) in vec3 _color;

        out vec3 Color;

        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;

        void main()
        {
            gl_Position = projection * view * model * vec4(_position, 1.0);

            Color = _color;

        }
	    )";

    std::string fs = R"(
		#version 410 core
        out vec4 FragColor;

        in vec3 Color;

        void main()
        {
            FragColor = vec4(Color,1);
        }
        )";

    line_shader_ptr = std::make_shared<GLSLShader>();
    line_shader_ptr->LoadShaderFromString(vs, fs, std::string{});
}

bool Line::GenGLBuffers()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // store instance data in an array buffer
    // --------------------------------------
    glGenBuffers(1, &instance_pos_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_pos_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _points.size(), &_points[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &instance_color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _color.size(), &_color[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Line::SetSceneInfo(GLFWwindow *_window_id, Scene &scene)
{
    int width  = 100;
    int height = 100;
    glfwGetWindowSize(_window_id, &width, &height);
    line_shader_ptr->activate();
    line_shader_ptr->setMat4("model", glm::mat4(1));
    line_shader_ptr->setMat4("view", scene.GetCamera().GetViewMatrix());
    line_shader_ptr->setMat4("projection", scene.GetCamera().GetPerspectiveMatrix((float)width / (float)height));
    line_shader_ptr->deactivate();
}

void Line::Draw(unsigned int type)
{
    // glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST); // Antialias the lines
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(line_shader_ptr->GetShaderID());
    glBindVertexArray(VAO);

    switch (type)
    {
        case GL_LINES:
            glDrawArrays(GL_LINES, 0, _points.size());
            break;
        case GL_LINE_STRIP:
            glDrawArrays(GL_LINE_STRIP, 0, _points.size());
            break;
        default:
            break;
    }

    glBindVertexArray(0);
    glUseProgram(0);
}
