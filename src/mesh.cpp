//
// Created by refantasy on 2022/6/20.
//

#include "mesh.h"

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

    glPointSize(_size > 0 ? _size : 1.0f);
    // glDrawElements(GL_POINTS, _indices.size(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_POINTS, 0, _vertices.size());

    glBindVertexArray(0);
    glUseProgram(0);
}
