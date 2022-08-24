

#include "camera.h"

glm::vec3 tmp_up;
float Camera::fov = 45;

Camera::Camera(glm::vec3 cam_pos, glm::vec3 cam_tar, glm::vec3 up) : cameraPos(cam_pos), cameraTarget(cam_tar)
{
    tmp_up = up;
    Update();
}
Camera &Camera::UpdateCamPos(glm::vec3 cam_pos)
{
    cameraPos = cam_pos;
    Update();
    return *this;
}
Camera &Camera::UpdateCamTar(glm::vec3 cam_tar)
{
    cameraTarget = cam_tar;
    Update();
    return *this;
}
Camera &Camera::UpdateCamUp(glm::vec3 cam_up)
{
    tmp_up = cam_up;
    Update();
    return *this;
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
    cameraRight = glm::normalize(glm::cross(tmp_up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
}
