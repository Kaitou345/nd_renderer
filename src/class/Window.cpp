#include <pch.h>
#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	memset(m_Keys, false, sizeof(m_Keys));
	m_MouseFirstMoved = true;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (m_Window == nullptr)
	{
		std::cout << "Window init returned error" << std::endl;
		glfwTerminate();
	}

	glfwGetFramebufferSize(m_Window, &m_bufferWidth, &m_bufferHeight);

	glfwMakeContextCurrent(m_Window);

	glViewport(0, 0, m_bufferWidth, m_bufferWidth);

	// Input callbacks
	glfwSetKeyCallback(m_Window, ProcessKeyInput);
	glfwSetCursorPosCallback(m_Window, ProcessMouseInput);

	// Sets the owner object pointer of the window
	glfwSetWindowUserPointer(m_Window, this);

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
}

bool Window::WindowShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

float Window::GetxOffset()
{
	float offset = m_xOffset;
	m_xOffset = 0;
	return offset;
}

float Window::GetyOffset()
{
	float offset = m_yOffset;
	m_yOffset = 0;

	return offset;
}

void Window::ClearColor(float R, float G, float B, float A)
{
	glClearColor(R, G, B, A);
}

void Window::Clear(int bitsToClear)
{
	glClear(bitsToClear);
}

void Window::ProcessKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if ((key >= 0 && key <= 1024))
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, true);
		}
		if (action == GLFW_PRESS)
		{
			currentWindow->m_Keys[key] = true;
		}
		if (action == GLFW_RELEASE)
		{
			currentWindow->m_Keys[key] = false;
		}
	}
}

void Window::ProcessMouseInput(GLFWwindow* window, double xPos, double yPos)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (currentWindow->m_MouseFirstMoved)
	{
		currentWindow->m_xPosLast = xPos;
		currentWindow->m_yPosLast = yPos;

		currentWindow->m_MouseFirstMoved = false;
	}

	currentWindow->m_xOffset = currentWindow->m_xPosLast - xPos;
	currentWindow->m_yOffset = currentWindow->m_yPosLast - yPos;

	currentWindow->m_xPosLast = xPos;
	currentWindow->m_yPosLast = yPos;
}