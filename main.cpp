#include "src/gui.h"
#include "src/mesh.h"

std::vector<Vertex> vertices;
std::vector<unsigned int> indices;
Mesh mesh(vertices, indices);

class GUI3D : public GUI
{
  public:
    using GUI::GUI;

    void Render() override
    {
        mesh.Draw(this->_shader.GetShaderID());
    }
};

int main(int argc, char *argv[])
{
    GUI3D gui;

    Vertex v1;
    Vertex v2;
    Vertex v3;
    Vertex v4;
    v1.Position = glm::vec3(0.5f, 0.5f, 0.0f);
    v1.Color = glm::vec3(1, 0, 0);
    v2.Position = glm::vec3(0.5f, -0.5f, 0.0f);
    v2.Color = glm::vec3(0, 0, 1.0);
    v3.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
    v3.Color = glm::vec3(1, 0.5, 0);
    v4.Position = glm::vec3(-0.5f, 0.5f, 0.0f);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    mesh._vertices = vertices;
    mesh._indices = indices;
    mesh.GenGLBuffers();

    // shader.BuildInShader();

    gui.MainLoop();

    return 0;
}
