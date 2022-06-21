#include "src/gui/gui.h"
#include "src/gui/mesh.h"
#include <memory>
#include <random>
#include <numeric>
template <typename T, typename Distribution = std::uniform_real_distribution<T>>
T RandomNumber(const T &lo = 0, const T &hi = 1)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    Distribution dist(lo, hi);
    return dist(rng);
}

std::shared_ptr<Mesh> ground;
std::shared_ptr<Mesh> CreateGround();
std::shared_ptr<Sphere> sphere;
std::shared_ptr<Sphere> CreateSphere();

class GUI3D : public GUI
{
  public:
    using GUI::GUI;

    void Render() override
    {

        ground->Draw(this->_shader.GetShaderID());
        sphere->Draw(this->_shader.GetShaderID());

    }
};

int main(int argc, char *argv[])
{
    GUI3D gui(800, 600);
    gui.SetBackGroundColor({0,0,0,0});
    GUI3D::SetVsync();

    ground = CreateGround();
    sphere = CreateSphere();

    gui.GetCamera().UpdateCamPos(glm::vec3{0, 20, 20});

    gui.Show();

    return 0;
}

std::shared_ptr<Mesh> CreateGround()
{
    Vertex v1,v2,v3,v4;
    float max_value = 10;
    v1.Position = glm::vec3 (max_value,0.0f,max_value);
    v2.Position = glm::vec3 (max_value,0.0f,-max_value);
    v3.Position = glm::vec3 (-max_value,0.0f,-max_value);
    v4.Position = glm::vec3 (-max_value,0.0f,max_value);


    v1.Color = glm::vec3 (RandomNumber<float>(0,1),RandomNumber<float>(0,1),RandomNumber<float>(0,1));
    v2.Color = glm::vec3 (RandomNumber<float>(0,1),RandomNumber<float>(0,1),RandomNumber<float>(0,1));
    v3.Color = glm::vec3 (RandomNumber<float>(0,1),RandomNumber<float>(0,1),RandomNumber<float>(0,1));
    v4.Color = glm::vec3 (RandomNumber<float>(0,1),RandomNumber<float>(0,1),RandomNumber<float>(0,1));

    std::vector<Vertex> vertexes{v1,v2,v3,v4};
    std::vector<unsigned int> indices{0,1,3,1,2,3};

    auto g = std::make_shared<Mesh>(vertexes, indices);
    g->GenGLBuffers();
    return g;
}
std::shared_ptr<Sphere> CreateSphere()
{
    Vertex s1,s2,s3;
    s1.Position = glm::vec3 (RandomNumber<float>(-8,8),RandomNumber<float>(1,5),RandomNumber<float>(-8,8));
    s1.Color = glm::vec3 (1,0,0);
    s2.Position = glm::vec3 (RandomNumber<float>(-8,8),RandomNumber<float>(1,5),RandomNumber<float>(-8,8));
    s2.Color = glm::vec3 (0,1,0);
    s3.Position = glm::vec3 (RandomNumber<float>(-8,8),RandomNumber<float>(1,5),RandomNumber<float>(-8,8));
    s3.Color = glm::vec3 (0,0,1);


    std::vector<Vertex> s_v{s1,s2,s3};
    auto s = std::make_shared<Sphere>(s_v, 3,32);
    s->GenGLBuffers();

    return s;
}
