#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cfloat>
#include <vector>

class Camera
{
  public:
    Camera(glm::vec3 cam_pos = glm::vec3(0, 0, 1), glm::vec3 cam_tar = glm::vec3(0, 0, 0),
           glm::vec3 up = glm::vec3(0, 1, 0))
        : cameraPos(cam_pos), cameraTarget(cam_tar), in_up(up)
    {
        Update();
    }

    void UpdateCamPos(glm::vec3 cam_pos)
    {
        cameraPos = cam_pos;
        Update();
    }
    void UpdateCamTar(glm::vec3 cam_tar)
    {
        cameraTarget = cam_tar;
        Update();
    }
    void UpdateCamUp(glm::vec3 cam_up)
    {
        in_up = cam_up;
        Update();
    }

  public:
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(cameraPos, cameraTarget, cameraUp);
    }

    glm::mat4 GetPerspectiveMatrix(float w_div_h)
    {
        return glm::perspective(glm::radians(fov), w_div_h, zNear, zFar);
    }

  private:
    glm::vec3 in_up;
    void Update() noexcept
    {
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        cameraRight = glm::normalize(glm::cross(in_up, cameraDirection));
        cameraUp = glm::cross(cameraDirection, cameraRight);
    }

  private:
    // 相机位置
    glm::vec3 cameraPos;
    // 相机看向的位置
    glm::vec3 cameraTarget;
    // 相机右侧方向
    glm::vec3 cameraRight;
    // 相机向上方向
    glm::vec3 cameraUp;

    // MY
    float zNear = 0.001, zFar = FLT_MAX / 2.0f, fov = 60;
};
#endif
