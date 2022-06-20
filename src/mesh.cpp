//
// Created by refantasy on 2022/6/20.
//

#include "mesh.h"
#include "iostream"

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool Mesh::GenGLBuffers()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0],
                 GL_STATIC_DRAW); // GL_STATIC_DRAW GL_DYNAMIC_DRAW
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    // vertex Color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Color));

    glBindVertexArray(0);

    return true;
}

void Mesh::Draw(GLuint shader_program)
{
    glUseProgram(shader_program);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Points::Draw(GLuint shader_program)
{
    glUseProgram(shader_program);
    glBindVertexArray(VAO);

    glDrawArrays(GL_POINTS, 0, _vertices.size());

    glBindVertexArray(0);
    glUseProgram(0);
}

SphereGen::SphereGen()
{
    init(24);
}

SphereGen::SphereGen(int prec)
{
    init(prec);
}

float SphereGen::toRadians(float degrees)
{
    return (degrees * 2.0f * 3.14159f) / 360.0f;
}

void SphereGen::init(int prec)
{
    numVertices = (prec + 1) * (prec + 1);
    numIndices = prec * prec * 6;
    for (int i = 0; i < numVertices; i++)
    {
        vertices.push_back(glm::vec3());
    }
    for (int i = 0; i < numVertices; i++)
    {
        texCoords.push_back(glm::vec2());
    }
    for (int i = 0; i < numVertices; i++)
    {
        normals.push_back(glm::vec3());
    }
    for (int i = 0; i < numVertices; i++)
    {
        tangents.push_back(glm::vec3());
    }
    for (int i = 0; i < numIndices; i++)
    {
        indices.push_back(0);
    }

    // calculate triangle vertices
    for (int i = 0; i <= prec; i++)
    {
        for (int j = 0; j <= prec; j++)
        {
            float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
            float x = -(float)cos(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
            float z = (float)sin(toRadians(j * 360.0f / (float)(prec))) * (float)abs(cos(asin(y)));
            vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);
            texCoords[i * (prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
            normals[i * (prec + 1) + j] = glm::vec3(x, y, z);

            // calculate tangent vector
            if (((x == 0) && (y == 1) && (z == 0)) || ((x == 0) && (y == -1) && (z == 0)))
            {
                tangents[i * (prec + 1) + j] = glm::vec3(0.0f, 0.0f, -1.0f);
            }
            else
            {
                tangents[i * (prec + 1) + j] = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(x, y, z));
            }
        }
    }
    // calculate triangle indices
    for (int i = 0; i < prec; i++)
    {
        for (int j = 0; j < prec; j++)
        {
            indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
            indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
            indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
            indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
            indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
            indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
        }
    }
}

int SphereGen::getNumVertices()
{
    return numVertices;
}
int SphereGen::getNumIndices()
{
    return numIndices;
}
std::vector<int> SphereGen::getIndices()
{
    return indices;
}
std::vector<glm::vec3> SphereGen::getVertices()
{
    return vertices;
}
std::vector<glm::vec2> SphereGen::getTexCoords()
{
    return texCoords;
}
std::vector<glm::vec3> SphereGen::getNormals()
{
    return normals;
}
std::vector<glm::vec3> SphereGen::getTangents()
{
    return tangents;
}

Sphere::Sphere(std::vector<Vertex> vertices, std::vector<float> radius, int prec) //: Mesh(std::move(vertices), {})
{
    std::vector<Vertex> tmp = vertices;
    _vertices.clear();

    SphereGen sg{prec};
    auto st_v = sg.getVertices();
    auto st_i = sg.getIndices();
    // 每个顶点生成一个球体
    for (int i = 0; i < tmp.size(); i++)
    {

        auto scale = radius[i];
        // 索引
        int base = _vertices.size();
        for (int j = 0; j < st_i.size(); j++)
        {
            _indices.push_back(st_i[j] + base);
        }

        // 顶点
        for (int j = 0; j < st_v.size(); j++)
        {
            Vertex v;
            v.Position = glm::vec3(st_v[j].x * scale, st_v[j].y * scale, st_v[j].z * scale) + tmp[i].Position;
            v.Color = tmp[i].Color;
            _vertices.push_back(v);
        }
    }
}
