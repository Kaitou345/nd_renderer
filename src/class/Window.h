#ifndef WINDOW
#define WINDOW

#include <pch.h>

class Window
{
public:
	Window(unsigned int width, unsigned int height, const char* title = "untitled window");
	~Window();
	bool WindowShouldClose();

	inline float GetBufferHeight() { return m_bufferHeight; }
	inline float GetBufferWidth() { return m_bufferWidth; }
	inline void SwapBuffers() { glfwSwapBuffers(m_Window); }
	inline GLFWwindow* GetWindowPointer() { return m_Window; }

	// Input getters
	inline bool* GetKeys() { return m_Keys; }
	float GetxOffset();
	float GetyOffset();

	inline void SetInterval(int interval) { glfwSwapInterval(interval); }
	void ClearColor(float R, float G, float B, float A);
	void Clear(int bitsToClear);
private:
	GLFWwindow* m_Window;
	int m_bufferHeight, m_bufferWidth;

	// Key input data
	bool m_Keys[1024];

	// Mouse Input data
	bool m_MouseFirstMoved;
	float m_xPosLast, m_yPosLast;
	float m_xOffset, m_yOffset;

	// Callback functions
	static void ProcessKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void ProcessMouseInput(GLFWwindow* window, double xPos, double yPos);
};

#endif