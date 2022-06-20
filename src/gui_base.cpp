//
// Created by refantasy on 2022/6/20.
//

#include "gui_base.h"

int GUIBase::InitOpenGL()
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	_window_id = glfwCreateWindow(_width, _height, _window_title.c_str(), NULL, NULL);
	if (!_window_id)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(_window_id);
	/* Enable vsync */
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(_window_id,[](GLFWwindow* window, int width, int height){ glViewport(0, 0, width, height); });

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	return 0;
}

void GUIBase::MainLoop()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(_window_id))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(_bg_color[0], _bg_color[1], _bg_color[2], _bg_color[3]);

		Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(_window_id);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}