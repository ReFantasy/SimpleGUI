#include "src/gui.h"
#include "src/mesh.h"
#include <random>

template <typename T, typename Distribution = std::uniform_real_distribution<T>>
T RandomNumber(const T &lo = 0, const T &hi = 1)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    Distribution dist(lo, hi);
    return dist(rng);
}

void PrintGLInfo()
{
    printf("\n-------------------------------- OpenGL Infomation -------------------------------\n");
    printf("  GL_VENDOR  :             %s\n", glGetString(GL_VENDOR));
    printf("  GL_RENDERER:             %s\n", glGetString(GL_RENDERER));
    printf("  GL_VERSION :             %s\n", glGetString(GL_VERSION));
    printf("  GLU_VERSION:             %s\n", gluGetString(GLU_VERSION));
    GLint buffers = 0, samples = 0;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &buffers);
    glGetIntegerv(GL_SAMPLES, &samples);
    if (buffers != 0)
        printf("  GL MULTISAMPLE ON:       buffers %d   samples  %d\n", buffers, samples);
}

std::vector<Vertex> vertices;
std::vector<unsigned int> indices;
Mesh mesh(vertices, indices);
Points pts{};
Sphere sp{};

class GUI3D : public GUI
{
  public:
    using GUI::GUI;

    void Render() override
    {
        // mesh.Draw(this->_shader.GetShaderID());
        //  pts.Draw(this->_shader.GetShaderID());
        sp.Draw(this->_shader.GetShaderID());
    }
};

int main(int argc, char *argv[])
{

    GUI3D gui(800, 800);

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

    pts = Points(vertices);
    pts.GenGLBuffers();
    pts.SetPointSize(4);

    std::vector<float> Rs;
    vertices.clear();
    for (int i = 0; i < 300; i++)
    {
        Rs.push_back(0.01);
        Vertex v;
        v.Position = glm::vec3(RandomNumber(-1.0f, 1.0f), RandomNumber(-1.0f, 1.0f), 0);
        v.Color = glm::vec3(RandomNumber(0.0f, 1.0f), RandomNumber(0.0f, 1.0f), RandomNumber(0.0f, 1.0f));
        vertices.push_back(v);
    }

    sp = Sphere(vertices, Rs, 12);
    sp.GenGLBuffers();

    gui.SetVsync();

    gui.Show();

    return 0;
}
