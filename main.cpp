#include "gui.h"
#include "iostream"
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
    gui.Show();

    return 0;
}