//
// Created by ReFantasy on 2022/8/16.
//

#include "sphere.h"

#include "GLFW/glfw3.h"

#include <utility>
Sphere::Sphere(std::vector<glm::vec3> positions, std::vector<float> radius, std::vector<glm::vec3> color, int prec)
    : _positions(std::move(positions)), _radius(std::move(radius)), _color(std::move(color))
{
    // calculate triangle vertices
    int numVertices = (prec + 1) * (prec + 1);
    int numIndices  = prec * prec * 6;
    std::vector<glm::vec3> st_v(numVertices, glm::vec3{});
    std::vector<unsigned int> st_i(numIndices, 0);
    for (int i = 0; i <= prec; i++)
    {
        for (int j = 0; j <= prec; j++)
        {
            float y                  = (float)cos(glm::radians(180.0f - i * 180.0f / prec));
            float x                  = -(float)cos(glm::radians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
            float z                  = (float)sin(glm::radians(j * 360.0f / (float)(prec))) * (float)abs(cos(asin(y)));
            st_v[i * (prec + 1) + j] = glm::vec3(x, y, z);
        }
    }
    // calculate triangle indices
    for (int i = 0; i < prec; i++)
    {
        for (int j = 0; j < prec; j++)
        {
            st_i[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
            st_i[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
            st_i[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
            st_i[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
            st_i[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
            st_i[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
        }
    }

    // 索引
    sphere_indices = std::move(st_i);

    // 顶点
    sphere_vertices = std::move(st_v);

    // 球的着色器
    std::string vs = R"(
		#version 410 core
        layout(location = 0) in vec3 _vertex;
		layout(location = 1) in vec3 _position;
		layout(location = 2) in vec3 _color;
        layout(location = 3) in float _radius;

        out vec3 FragPos;
        out vec3 Normal;
        out vec3 Color;

        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;

        void main()
        {
            vec3 vertex_pos = _vertex * _radius;
            FragPos = vec3(model*vec4(vertex_pos + _position, 1.0f));
            Normal = _vertex;
            gl_Position = projection * view *vec4(FragPos, 1.0);

            Color = _color;
            //Color = vec3(1,1,0);
        }
	    )";

    std::string fs = R"(
		#version 410 core
        out vec4 FragColor;

        struct Material {
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
            float shininess;
        };
        struct Light
        {
            vec3 position;
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };

        in vec3 FragPos;
        in vec3 Normal;
        in vec3 Color;

        uniform vec3 viewPos;
        uniform Material material;
        uniform Light light;
        uniform bool use_vertex_color;



        void main()
        {
            vec3 ma = material.ambient;
            vec3 md = material.diffuse;

            # 使用顶点颜色渲染
            if(use_vertex_color)
            {
                ma = Color;
                md = Color;
            }

            // ambient
            vec3 ambient = light.ambient * ma;

            // diffuse
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(light.position - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = light.diffuse * (diff * md);

            // specular
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            vec3 specular = light.specular * (spec * material.specular);

            vec3 result = ambient + diffuse + specular;
            FragColor = vec4(result, 1.0);
            //FragColor = vec4(Color, 1.0);
        }
        )";

    sphere_shader.LoadShaderFromString(vs, fs, std::string{});
    sphere_shader.activate();
    sphere_shader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
    sphere_shader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    sphere_shader.setVec3("material.specular", glm::vec3(0.15f, 0.15f, 0.15f));
    sphere_shader.setFloat("material.shininess", 32);
    sphere_shader.UseVertexColor();
    sphere_shader.deactivate();
}
bool Sphere::GenGLBuffers()
{
    glGenVertexArrays(1, &VAO);

    // store instance data in an array buffer
    // --------------------------------------
    glGenBuffers(1, &instance_pos_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_pos_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _positions.size(), &_positions[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &instance_color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _color.size(), &_color[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &instance_radius_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_radius_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _radius.size(), &_radius[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // create buffers/arrays

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(glm::vec3), &sphere_vertices[0],
                 GL_STATIC_DRAW); // GL_STATIC_DRAW GL_DYNAMIC_DRAW
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere_indices.size() * sizeof(unsigned int), &sphere_indices[0], GL_DYNAMIC_DRAW);

    // set the vertex attribute pointers
    // vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    // also set instance data
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, instance_pos_vbo); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1); // tell OpenGL this is an instanced vertex attribute.

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instance_color_vbo); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, instance_radius_vbo); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);

    glBindVertexArray(0);
}
void Sphere::Draw()
{
    glUseProgram(sphere_shader.GetShaderID());
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES,sphere_indices.size(), GL_UNSIGNED_INT, 0, _positions.size());
    glBindVertexArray(0);
    glUseProgram(0);
}
void Sphere::SetSceneInfo(GLFWwindow *_window_id, Scene &scene)
{
    int width =100;
    int height = 100;
    glfwGetWindowSize(_window_id, &width, &height);
    sphere_shader.activate();
    sphere_shader.setVec3("viewPos", scene.GetCamera().GetCameraPosition());

    sphere_shader.setMat4("model", glm::mat4(1));
    sphere_shader.setMat4("view", scene.GetCamera().GetViewMatrix());
    sphere_shader.setMat4("projection",
                          scene.GetCamera().GetPerspectiveMatrix((float)width / (float)height));

    sphere_shader.setVec3("light.position", scene.GetLight().position);
    sphere_shader.setVec3("light.ambient", scene.GetLight().ambient);
    sphere_shader.setVec3("light.diffuse", scene.GetLight().diffuse);
    sphere_shader.setVec3("light.specular", scene.GetLight().specular);

    sphere_shader.deactivate();
}
