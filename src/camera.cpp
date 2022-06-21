

#include "camera.h"

glm::vec3 in_up;

Camera::Camera(glm::vec3 cam_pos, glm::vec3 cam_tar, glm::vec3 up) : cameraPos(cam_pos), cameraTarget(cam_tar)
{
    in_up = up;
    Update();
}
void Camera::UpdateCamPos(glm::vec3 cam_pos)
{
    cameraPos = cam_pos;
    Update();
}
void Camera::UpdateCamTar(glm::vec3 cam_tar)
{
    cameraTarget = cam_tar;
    Update();
}
void Camera::UpdateCamUp(glm::vec3 cam_up)
{
    in_up = cam_up;
    Update();
}
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPos, cameraTarget, cameraUp);
}
glm::mat4 Camera::GetPerspectiveMatrix(float w_div_h)
{
    return glm::perspective(glm::radians(fov), w_div_h, zNear, zFar);
}
void Camera::Update() noexcept
{
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(in_up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
}
