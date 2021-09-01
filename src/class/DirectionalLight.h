#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "Light.h"
#include "shader.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight() {}
	DirectionalLight(glm ::vec3 color, glm::vec3 direction, float intensity);
	void Update(glm::vec3 color, glm::vec3 direction, float intensity);

	void Bind(Shader& shader);

	glm::vec3 GetColor();
	glm::vec3 GetDirection();
	float GetIntensity();

private:
	glm::vec3 m_Direction;
};

#endif