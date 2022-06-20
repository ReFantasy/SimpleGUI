//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_GUI_H
#define GUI_GUI_H

#include <iostream>
#include <string>
#include <utility>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Eigen/Core"

class GUIBase
{
public:
	explicit GUIBase(int width = 600, int height = 600, std::string title = "OpenGL Window",
			Eigen::Vector4f bg_color = Eigen::Vector4f{ 0, 0, 0, 1 })
			: _width(width), _height(height), _window_title(std::move(title)), _bg_color(std::move(bg_color))
	{
		InitOpenGL();
	}

	void MainLoop();



protected:
	GLFWwindow* _window_id = nullptr;

	int _width = 600;
	int _height = 600;

	// background color
	Eigen::Vector4f _bg_color{ 0, 0, 0, 1 };

	// title of window
	std::string _window_title = std::string("OpenGL Window");

private:
	int InitOpenGL();
};


#endif //GUI_GUI_H
