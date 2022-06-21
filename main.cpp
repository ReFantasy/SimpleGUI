#include "src/gui.h"
#include "src/mesh.h"
#include <random>

class GUI3D : public GUI
{
  public:
    using GUI::GUI;

    void Render() override
    {
    }
};

int main(int argc, char *argv[])
{

    GUI3D gui(800, 600);

    GUI3D::SetVsync();
    gui.GetCamera().UpdateCamPos(glm::vec3{0, 0, 6});
    gui.Show();

    return 0;
}
