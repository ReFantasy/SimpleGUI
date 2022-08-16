//
// Created by ReFantasy on 2022/8/16.
//

#ifndef GUI_SPHERE_H
#define GUI_SPHERE_H

#include "glm/glm.hpp"
#include "glsl_shader.h"
#include <string>
#include <vector>
#include "scene.h"

class Sphere
{
    friend class Scene;
public:
    explicit Sphere(std::vector<glm::vec3> positions = std::vector<glm::vec3>{},
                     std::vector<float> radius        = std::vector<float>{},
                     std::vector<glm::vec3> color = std::vector<glm::vec3>{}, int prec = 48);

    virtual ~Sphere()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    bool GenGLBuffers();

    void Draw();

    void SetSceneInfo(GLFWwindow *window_id, Scene &scene);

    // protected:
    std::vector<glm::vec3> sphere_vertices;
    std::vector<unsigned int> sphere_indices;
    std::vector<glm::vec3> _positions;
    std::vector<float> _radius;
    std::vector<glm::vec3> _color;

    GLSLShader sphere_shader;

//protected:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    unsigned int instance_pos_vbo;
    unsigned int instance_color_vbo;
    unsigned int instance_radius_vbo;
};

#endif // GUI_SPHERE_H
