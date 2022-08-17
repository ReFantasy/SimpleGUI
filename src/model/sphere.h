/**
 * Sphere Class
 * 分别给定球心、半径、颜色三个数组，创建一组球体
 * 球体使用预定义的着色器进行着色
 * 在绘制的时候，需要先传入窗口ID和场景信息(光源和相机)
 */

#ifndef GUI_SPHERE_H
#define GUI_SPHERE_H

#include "glm/glm.hpp"

#include "scene.h"
#include <string>
#include <vector>

class GLSLShader;
class GLFWwindow;

class Sphere
{
    friend class Scene;

public:
    /**
     * 默认构造
     * @param positions 球心坐标数组
     * @param radius 半径数组
     * @param color 颜色数组
     * @param precision 渲染精度
     */
    explicit Sphere(std::vector<glm::vec3> positions = std::vector<glm::vec3>{},
                    std::vector<float> radius        = std::vector<float>{},
                    std::vector<glm::vec3> color = std::vector<glm::vec3>{}, int precision = 48);

    /**
     * 生成 OpenGL 缓冲对象
     * @return
     */
    bool GenGLBuffers();

    /**
     * 获取窗口信息和场景中的光源相机等信息以便于渲染
     * @param window_id 窗口ID
     * @param scene 窗口(GUI)中的场景对象
     */
    void SetSceneInfo(GLFWwindow *window_id, Scene &scene);

    /**
     *  使用预定义的着色器进行渲染
     */
    void Draw();

    /**
     * 返回着色器对象
     * @return
     */
    std::shared_ptr<GLSLShader> &Shader()
    {
        return sphere_shader;
    }

    virtual ~Sphere();

protected:
    /* 单位球的顶点 */
    std::vector<glm::vec3> sphere_vertices;
    /* 球体三角面片索引 */
    std::vector<unsigned int> sphere_indices;

    /* 实例化球的坐标 */
    std::vector<glm::vec3> _positions;
    /* 实例化球的半径 */
    std::vector<float> _radius;
    /* 实例化球的颜色 */
    std::vector<glm::vec3> _color;

    /* 着色器对象 */
    std::shared_ptr<GLSLShader> sphere_shader;

    /* OpenGL 缓冲对象 */
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    unsigned int instance_pos_vbo;
    unsigned int instance_color_vbo;
    unsigned int instance_radius_vbo;
};

#endif // GUI_SPHERE_H
