#include "src/gui/gui.h"
#include "src/gui/mesh.h"
#include <filesystem>
#include <memory>
#include <random>
#include <string>
#include <iostream>

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
std::shared_ptr<Mesh> box;
std::shared_ptr<Mesh> CreateBox();

class GUI3D : public GUI
{
  public:
    using GUI::GUI;

    void Render() override
    {
        /**
         * 定义随时间变换的光源
         */
        glm::vec3 lightColor;
        lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
        lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f);   // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

        Light new_light;
        new_light.position = glm::vec3(0, 2, 2);
        new_light.ambient = ambientColor;
        new_light.diffuse = diffuseColor;
        new_light.specular = glm::vec3(1, 1, 1);
        scene.GetLight() = new_light;

        /**
         * 渲染物体
         */
        _shader.UseVertexColor(false);
        _shader.SetColor(glm::vec3(0.7, 0.7, 0.7));
        ground->Draw(this->_shader.GetShaderID());

        _shader.UseVertexColor(true);
        box->Draw(this->_shader.GetShaderID());
        sphere->Draw(this->_shader.GetShaderID());
    }
};

int main(int argc, char *argv[])
{
    std::filesystem::path source_dir(PROJECT_SOURCE_DIR);

    GUI3D gui(800, 600);
    gui.SetBackGroundColor({0, 0, 0},0.1);
    //GUI3D::SetVsync(false);

    gui.scene.GetCamera().UpdateCamPos(glm::vec3{3, 3, 3}).UpdateCamTar(glm::vec3(0, 0, 0));
    gui.scene.GetLight().position = glm::vec3(0, 2, 2);

    box = CreateBox();
    box->LoadDiffuseMap(std::string(source_dir.string() + "/resource/container2.png").c_str());
    box->LoadSpecularMap(std::string(source_dir.string() + "/resource/container2_specular.png").c_str());

    sphere = CreateSphere();

    ground = CreateGround();

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
std::shared_ptr<Mesh> CreateBox()
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
        v.Color = 0.5f * v.Position + glm::vec3(0.6, 0.3, 0.3);
        VV.push_back(v);
        indices.push_back(i);
    }

    auto g = std::make_shared<Mesh>(VV, indices);
    g->GenGLBuffers();
    return g;
}
