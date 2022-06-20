//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_MESH_H
#define GUI_MESH_H

#include "GL/glew.h"
#include "glm/glm.hpp"
#include <utility>
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
                  std::vector<unsigned int> indices = std::vector<unsigned int>{})
        : _vertices(std::move(vertices)), _indices(std::move(indices)){};

    virtual ~Mesh();

    bool GenGLBuffers();

    /**
     * @brief
     */
    void UpdateVertexDataToGLBuffer()
    {
        glBindVertexArray(VAO);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
    }

    virtual void Draw(GLuint shader_program);

    // protected:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;

  protected:
    GLuint VAO = 0, VBO = 0, EBO = 0;
};

class Points : public Mesh
{
  public:
    explicit Points(std::vector<Vertex> vertices = std::vector<Vertex>{}) : Mesh(std::move(vertices), {})
    {
    }
    void Draw(GLuint shader_program) override;
    void SetPointSize(float sz)
    {
        glPointSize(sz > 0 ? sz : 1.0f);
    }
};

class SphereGen
{
  private:
    int numVertices;
    int numIndices;
    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    void init(int);
    float toRadians(float degrees);

  public:
    SphereGen();
    SphereGen(int prec);
    int getNumVertices();
    int getNumIndices();
    std::vector<int> getIndices();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getTexCoords();
    std::vector<glm::vec3> getNormals();
    std::vector<glm::vec3> getTangents();
};

class Sphere : public Mesh
{
  public:
    explicit Sphere(std::vector<Vertex> vertices = std::vector<Vertex>{},
                    std::vector<float> radius = std::vector<float>{}, int prec = 48);
};
#endif // GUI_MESH_H
