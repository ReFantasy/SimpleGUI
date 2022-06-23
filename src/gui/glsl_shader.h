#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

class GLSLShader
{
  public:
    GLSLShader()
    {
        BuildInShader();
    }

    void BuildInShader()
    {
        std::string vs = R"(
		#version 410 core
        layout(location = 0) in vec3 _position;
		layout(location = 1) in vec3 _normal;
		layout(location = 2) in vec3 _color;

        out vec3 FragPos;
        out vec3 Normal;
        out vec3 Color;

        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;

        void main()
        {
            FragPos = vec3(model*vec4(_position, 1.0f));
            Normal = mat3(transpose(inverse(model))) * _normal;
            gl_Position = projection * view *vec4(FragPos, 1.0);

            Color = _color;
        }
	    )";

        std::string fs = R"(
		#version 410 core
        out vec4 FragColor;

        // struct Material
        // {
        //     sampler2D diffuse;
        //     sampler2D specular;
        //     float shininess;
        // };

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
        //uniform Material material;
        uniform Light light;

       
        void main()
        {
            vec3 material_ambient = Color;
            vec3 material_diffuse = Color;
            vec3 material_specular = vec3(0.2, 0.2, 0.2);
            float material_shininess = 64;

            // ambient
            vec3 ambient = light.ambient * material_diffuse;
            
            // diffuse 
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(light.position - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = light.diffuse * (diff * material_diffuse);
            
            // specular
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);  
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
            vec3 specular = light.specular * (spec * material_specular);  
                
            vec3 result = ambient + diffuse + specular;
            FragColor = vec4(result, 1.0);
        }
        )";

        LoadShaderFromString(vs, fs, std::string{});
    }

    unsigned int GetShaderID() const
    {
        return ID;
    }

    void LoadShaderFromFile(const char *vertexPath, const char *fragmentPath, const char *geometryPath = nullptr)
    {
        if (ID != 0)
        {
            glDeleteShader(ID);
            ID = 0;
        }

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
            if (geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        LoadShaderFromString(vertexCode, fragmentCode, geometryCode);

        activate();
        setInt("material.diffuse", 0);
        setInt("material.specular", 1);
        setFloat("material.shininess", 64.0f);
        deactivate();
    }

    void LoadShaderFromString(std::string vertexCode, std::string fragmentCode, std::string geometryCode)
    {
        if (ID != 0)
        {
            glDeleteShader(ID);
            ID = 0;
        }

        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        unsigned int geometry;
        if (!geometryCode.empty())
        {
            const char *gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (!geometryCode.empty())
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (!geometryCode.empty())
            glDeleteShader(geometry);
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void activate()
    {
        glUseProgram(ID);
    }

    void deactivate()
    {
        glUseProgram(0);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

  private:
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

  protected:
    unsigned int ID = 0;
};

#endif
