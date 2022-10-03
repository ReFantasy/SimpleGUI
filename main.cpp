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

    Mesh mesh;

    GLSLShader shader;

    gui.Show();
    return 0;
}