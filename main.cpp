#include "src/ext/model.h"
#include "src/gui/gui.h"
#include "src/gui/mesh.h"
#include <filesystem>
#include <memory>
#include <random>

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
std::shared_ptr<Mesh> cube;
std::shared_ptr<Mesh> CreateCube();

std::shared_ptr<Model> model;

class GUI3D : public GUI
{
  public:
    using GUI::GUI;

    void Render() override
    {
        _shader.activate();
        _shader.deactivate();

        ground->Draw(this->_shader.GetShaderID());
        cube->Draw(this->_shader.GetShaderID());
        sphere->Draw(this->_shader.GetShaderID());

        // model->Draw(this->_shader.GetShaderID());
    }
};

int main(int argc, char *argv[])
{
    std::filesystem::path source_dir(PROJECT_SOURCE_DIR);

    GUI3D gui(800, 600);
    gui.SetBackGroundColor({0, 0, 0, 0});
    GUI3D::SetVsync();

    gui.GetCamera().UpdateCamPos(glm::vec3{3, 3, 3.0}).UpdateCamTar(glm::vec3(0, 0.5, 0));
    gui.GetShader().LoadShaderFromFile(std::string(source_dir.string() + "/src/gui/basic_vs.glsl").c_str(),
                                       std::string(source_dir.string() + "/src/gui/basic_fs.glsl").c_str());
    gui.GetLight().position = glm::vec3(0, 2, 2);

    cube = CreateCube();
    cube->LoadDiffuseMap(std::string(source_dir.string() + "/resource/container2.png").c_str());
    cube->LoadSpecularMap(std::string(source_dir.string() + "/resource/container2_specular.png").c_str());

    sphere = CreateSphere();

    ground = CreateGround();

    model = std::make_shared<Model>(std::string(source_dir.string() + "/resource/NasaShuttle/shuttle.obj"));
    model->meshes[0].LoadDiffuseMap(std::string(source_dir.string() + "/resource/NasaShuttle/spstob_1.jpg"));

    gui.Show();

    return 0;
}

std::shared_ptr<Mesh> CreateGround()
{
    Vertex v1, v2, v3, v4;
    float max_value = 10;
    v1.Position = glm::vec3(max_value, 0.0f, max_value);
    v2.Position = glm::vec3(max_value, 0.0f, -max_value);
    v3.Position = glm::vec3(-max_value, 0.0f, -max_value);
    v4.Position = glm::vec3(-max_value, 0.0f, max_value);

    glm::vec3 normal(0, 1, 0);
    v1.Normal = v2.Normal = v3.Normal = v4.Normal = normal;

    v1.Color = glm::vec3(RandomNumber<float>(0, 1), RandomNumber<float>(0, 1), RandomNumber<float>(0, 1));
    v2.Color = glm::vec3(RandomNumber<float>(0, 1), RandomNumber<float>(0, 1), RandomNumber<float>(0, 1));
    v3.Color = glm::vec3(RandomNumber<float>(0, 1), RandomNumber<float>(0, 1), RandomNumber<float>(0, 1));
    v4.Color = glm::vec3(RandomNumber<float>(0, 1), RandomNumber<float>(0, 1), RandomNumber<float>(0, 1));

    std::vector<Vertex> vertexes{v1, v2, v3, v4};
    std::vector<unsigned int> indices{0, 1, 3, 1, 2, 3};

    auto g = std::make_shared<Mesh>(vertexes, indices);
    g->GenGLBuffers();
    return g;
}
std::shared_ptr<Sphere> CreateSphere()
{
    Vertex s1, s2, s3;
    s1.Position = glm::vec3(RandomNumber<float>(-2, 2), RandomNumber<float>(0.3, 1), RandomNumber<float>(-2, 2));
    s1.Color = glm::vec3(1, 0, 0);
    s2.Position = glm::vec3(RandomNumber<float>(-2, 2), RandomNumber<float>(0.3, 1), RandomNumber<float>(-2, 1));
    s2.Color = glm::vec3(0, 1, 0);
    s3.Position = glm::vec3(RandomNumber<float>(-2, 2), RandomNumber<float>(0.3, 1), RandomNumber<float>(-2, 2));
    s3.Color = glm::vec3(0, 0, 1);

    std::vector<Vertex> s_v{s1, s2, s3};
    auto s = std::make_shared<Sphere>(s_v, 0.3, 48);
    s->GenGLBuffers();

    return s;
}
std::shared_ptr<Mesh> CreateCube()
{
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f};

    std::vector<Vertex> VV;
    std::vector<unsigned int> indices;
    for (int i = 0; i < 36; i++)
    {
        Vertex v;
        int base = 8 * i;
        v.Position = glm::vec3(vertices[base + 0], vertices[base + 1], vertices[base + 2]) + glm::vec3(0, 0.6, 0);
        v.Normal = glm::vec3(vertices[base + 3], vertices[base + 4], vertices[base + 5]);
        v.Texcoord = glm::vec2(vertices[base + 6], vertices[base + 7]);
        VV.push_back(v);
        indices.push_back(i);
    }

    auto g = std::make_shared<Mesh>(VV, indices);
    g->GenGLBuffers();
    return g;
}
