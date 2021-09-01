#ifndef TIME
#define TIME

#include <pch.h>

class Time
{
public:
	Time() = delete;
	Time(const Time& other) = delete;

	static void Update()
	{
		s_deltaTime = glfwGetTime() - s_lastFrameTime;
		s_lastFrameTime = glfwGetTime();
	}

	static float GetDeltaTime()
	{
		return s_deltaTime;
	}

private:
	static float s_lastFrameTime;
	static float s_deltaTime;
};

float Time::s_lastFrameTime		{0.f};
float Time::s_deltaTime    		{0.f};

#endif