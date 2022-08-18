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

    // texture coord
    glm::vec2 Texcoord = glm::vec2{0, 0};
};

class Mesh
{
public:
    explicit Mesh(std::vector<Vertex> vertices      = std::vector<Vertex>{},
                  std::vector<unsigned int> indices = std::vector<unsigned int>{})
        : _vertices(std::move(vertices)), _indices(std::move(indices)){};

    virtual ~Mesh();

    bool GenGLBuffers();

    void LoadDiffuseMap(std::string image_path);
    void LoadSpecularMap(std::string image_path);

    /**
     * @brief
     */
    void UpdateVertexDataToGLBuffer();

    virtual void Draw(unsigned int shader_program);


    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;


protected:
    unsigned int VAO = 0, VBO = 0, EBO = 0;

private:
    unsigned int LoadTexture(std::string image_path);
    unsigned int diffuseMap;
    unsigned int specularMap;
};

//class Points : public Mesh
//{
//public:
//    explicit Points(std::vector<Vertex> vertices = std::vector<Vertex>{}) : Mesh(std::move(vertices), {})
//    {
//    }
//    void Draw(GLuint shader_program) override;
//    void SetPointSize(float sz)
//    {
//        glPointSize(sz > 0 ? sz : 1.0f);
//    }
//};

#endif // GUI_MESH_H
