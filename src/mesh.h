//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_MESH_H
#define GUI_MESH_H

#include "glm/glm.hpp"

#include <string>
#include <vector>

struct Vertex
{
    // position
    glm::vec3 Position = glm::vec3{0, 0, 0};

    // normal
    glm::vec3 Normal = glm::vec3{0, 1, 0};

    // color
    glm::vec3 Color = glm::vec3{1, 1, 1};
};

class Mesh
{
  public:
    explicit Mesh(std::vector<Vertex> vertices = std::vector<Vertex>{},
                  std::vector<unsigned int> indices = std::vector<unsigned int>{});

    virtual ~Mesh();

    void UpdateGLBuffer();

    virtual void Draw(unsigned int);

    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;

  private:
    bool GenGLBuffers();

  protected:
    unsigned int VAO = 0, VBO = 0, EBO = 0;
};

#endif // GUI_MESH_H