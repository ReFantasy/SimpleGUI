/*
 * Created by refantasy on 2022/6/21.
 *
 * 投射投影相机，配置相机参数并计算相关投影矩阵
 *
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include <cfloat>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Camera
{
  public:
    explicit Camera(glm::vec3 cam_pos = glm::vec3(0, 0, 1), glm::vec3 cam_tar = glm::vec3(0, 0, 0),
                    glm::vec3 up = glm::vec3(0, 1, 0));

    Camera &UpdateCamPos(glm::vec3 cam_pos);

    Camera &UpdateCamTar(glm::vec3 cam_tar);

    Camera &UpdateCamUp(glm::vec3 cam_up);

    glm::vec3 GetCameraPosition() const
    {
        return cameraPos;
    }

  public:
    glm::mat4 GetViewMatrix();

    glm::mat4 GetPerspectiveMatrix(float w_div_h);

  private:
    void Update() noexcept;

  private:
    // 相机位置
    glm::vec3 cameraPos;
    // 相机看向的位置
    glm::vec3 cameraTarget;
    // 相机右侧方向
    glm::vec3 cameraRight{};
    // 相机向上方向
    glm::vec3 cameraUp{};

  public:
    float zNear = 0.001;
    float zFar = FLT_MAX / 2.0f;
    float fov = 45;
};

#endif
