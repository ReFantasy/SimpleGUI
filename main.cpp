#include "glsl_shader.h"
#include "gui.h"
#include "iostream"
#include "mesh.h"
#include "random"

class GUI3D : public GUI
{
  public:
    void Render() override
    {
        // std::cout << "ok" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    GUI3D gui{};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    vertices.push_back(Vertex{});
    indices.push_back(0);
    Mesh mesh(vertices, indices);

    GLSLShader shader;

    gui.Show();
    return 0;
}
