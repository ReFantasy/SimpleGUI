#include "glm/fwd.hpp"
#include "glsl_shader.h"
#include "gui.h"
#include "iostream"
#include "memory"
#include "mesh.h"
#include "random"
#include <memory>

void MOUSE_BUTTON_CALLBACK(GLFWwindow *window, int button, int action,
                           int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
int g_mouse_buttons = 0, g_mouse_old_x = 0, g_mouse_old_y = 0;
float g_rotate_x = 0.0, g_rotate_y = 0.0, g_translate_z = 0.0;

std::shared_ptr<Mesh> mesh_ptr;

class GUI3D : public GUI
{
  public:
    void Render() override
    {
      glm::mat4 view = camera.GetViewMatrix();
      view = glm::translate(view, glm::vec3(0, 0, g_translate_z));
      view = glm::rotate(view, glm::radians(g_rotate_x), glm::vec3(1, 0, 0));
      view = glm::rotate(view, glm::radians(g_rotate_y), glm::vec3(0, 1, 0));
      _shader.setMat4("view", view);

      mesh_ptr->Draw(_shader.GetShaderID());
    }
};

std::shared_ptr<GUI3D> gui;

int main(int argc, char *argv[])
{
  // 创建GUI实例,并设置鼠标回调
  gui = std::make_shared<GUI3D>();

  glfwSetMouseButtonCallback(gui->GetWindowID(), MOUSE_BUTTON_CALLBACK);
  glfwSetCursorPosCallback(gui->GetWindowID(), mouse_callback);
  glfwSetScrollCallback(gui->GetWindowID(), scroll_callback);

  Vertex v1;
  v1.Position = glm::vec3(0, 0, 0);
  v1.Color = glm::vec3(1, 0, 0);
  Vertex v2;
  v2.Position = glm::vec3(1, 0, 0);
  Vertex v3;
  v3.Position = glm::vec3(0.5, 1, 0);
  std::vector<Vertex> vertices;
  vertices.push_back(v1);
  vertices.push_back(v2);
  vertices.push_back(v3);

  std::vector<unsigned int> indices;
  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  mesh_ptr = std::make_shared<Mesh>(vertices, indices);

  gui->Show();
  return 0;
}

void MOUSE_BUTTON_CALLBACK(GLFWwindow *window, int button, int action,
                           int mods) {
  if ((action == GLFW_PRESS) && (button == GLFW_MOUSE_BUTTON_LEFT)) {
    g_mouse_buttons |= 1 << button;
  } else if ((action == GLFW_RELEASE) && (button == GLFW_MOUSE_BUTTON_LEFT)) {
    g_mouse_buttons = 0;
  }

  double pos[2];
  glfwGetCursorPos(window, &pos[0], &pos[1]);
  g_mouse_old_x = pos[0];
  g_mouse_old_y = pos[1];
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
  float dx, dy;
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  dx = (float)(xpos - g_mouse_old_x);
  dy = (float)(ypos - g_mouse_old_y);

  if (g_mouse_buttons & 1) {
    g_rotate_x += dy * 0.2f;
    g_rotate_y += dx * 0.2f;
  } else if (g_mouse_buttons & 2) {
    g_translate_z += dy * 0.01f;
  }

  g_mouse_old_x = xpos;
  g_mouse_old_y = ypos;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  gui->camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
