#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "gui.h"

int main(int argc, char* argv[])
{
	GUIBase gui(800,600, "OPenGL", { 1, 0.5, 0, 0});

	gui.MainLoop();

	return 0;
}