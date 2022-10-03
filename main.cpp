#include "glm/fwd.hpp"
#include "glsl_shader.h"
#include "gui.h"
#include "iostream"
#include "memory"
#include "mesh.h"
#include "random"
#include <memory>

std::shared_ptr<Mesh> mesh_ptr;

class GUI3D : public GUI
{
  public:
    void Render() override
    {
        // std::cout << "ok" << std::endl;
        mesh_ptr->Draw(_shader.GetShaderID());
    }
};

std::shared_ptr<GUI3D> gui;

int main(int argc, char *argv[])
{
  gui = std::make_shared<GUI3D>();

  Vertex v1;
  v1.Position = glm::vec3(0, 0, 0);
  v1.Color = glm::vec3(1, 0, 0);
  Vertex v2;
  v2.Position = glm::vec3(1, 0, 0);
  Vertex v3;
  v3.Position = glm::vec3(0.5, 1, 0);
  std::vector<Vertex> vertices;
  vertices.push_back(v1);
  vertices.push_back(v2);
  vertices.push_back(v3);

  std::vector<unsigned int> indices;
  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  mesh_ptr = std::make_shared<Mesh>(vertices, indices);

  gui->Show();
  return 0;
}
