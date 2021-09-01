#ifndef GLINIT
#define GLINIT

#include "pch.h"

#define MAX_POINT_LIGHTS = 3;

/// Must be initialized before window creation
bool GlfwInit()
{
	// Initializaiton
	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "GLFW Init returned error";
		glfwTerminate();
		return false;
	}

	return true;
}

/// Must be initialized after window creation
bool GlewInit()
{
	// Modern OpenGL features
	glewExperimental = GL_TRUE;

	// Glew Initialization
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW init returned error";
		glfwTerminate();
		return false;
	}

	// GL Enables
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);

	return true;
}

#endif