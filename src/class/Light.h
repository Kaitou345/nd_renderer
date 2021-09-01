#ifndef LIGHT
#define LIGHT

#include <pch.h>

class Light
{
public:
	Light() = default;
	Light(glm::vec3 color, float intensity)
	{
		m_Color = color;
		m_Intensity = intensity;
	}
	virtual void Update(glm::vec3 color, float intensity)
	{
		m_Color = color;
		m_Intensity = intensity;
	}

	virtual glm::vec3 GetColor() { return m_Color;	}
	virtual float GetIntensity()	{ return m_Intensity; }

protected:
	glm::vec3 m_Color;
	float m_Intensity;
};

#endif