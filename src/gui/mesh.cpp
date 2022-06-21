//
// Created by refantasy on 2022/6/20.
//

#include "mesh.h"
#include "iostream"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

unsigned int Mesh::LoadTexture(std::string image_path)
{
    auto path = image_path.c_str();
    unsigned int textureID = 0;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
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
    // vertex texture coords
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Texcoord));

    glBindVertexArray(0);

    return true;
}

void Mesh::Draw(GLuint shader_program)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}
void Mesh::LoadDiffuseMap(std::string image_path)
{
    diffuseMap = LoadTexture(image_path);
}
void Mesh::LoadSpecularMap(std::string image_path)
{
    specularMap = LoadTexture(image_path);
}
void Points::Draw(GLuint shader_program)
{
    glUseProgram(shader_program);
    glBindVertexArray(VAO);

    glDrawArrays(GL_POINTS, 0, _vertices.size());

    glBindVertexArray(0);
    glUseProgram(0);
}


Sphere::Sphere(std::vector<Vertex> vertices, std::vector<float> radius, int prec)
{
    std::vector<Vertex> tmp = vertices;
    _vertices.clear();

    // calculate triangle vertices
    int numVertices = (prec + 1) * (prec + 1);
    int numIndices = prec * prec * 6;
    std::vector<glm::vec3> st_v(numVertices, glm::vec3{});
    std::vector<int> st_i(numIndices, 0);
    for (int i = 0; i <= prec; i++)
    {
        for (int j = 0; j <= prec; j++)
        {
            float y = (float)cos(glm::radians(180.0f - i * 180.0f / prec));
            float x = -(float)cos(glm::radians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
            float z = (float)sin(glm::radians(j * 360.0f / (float)(prec))) * (float)abs(cos(asin(y)));
            st_v[i * (prec + 1) + j] = glm::vec3(x, y, z);
        }
    }
    // calculate triangle indices
    for (int i = 0; i < prec; i++)
    {
        for (int j = 0; j < prec; j++)
        {
            st_i[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
            st_i[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
            st_i[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
            st_i[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
            st_i[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
            st_i[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
        }
    }

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
            v.Normal = st_v[j];
            v.Position = glm::vec3(st_v[j].x * scale, st_v[j].y * scale, st_v[j].z * scale) + tmp[i].Position;
            v.Color = tmp[i].Color;
            _vertices.push_back(v);
        }
    }
}
