#ifndef AMBIENT_LIGHT
#define AMBIENT_LIGHT

#include "Light.h"
#include "shader.h"


class AmbientLight : public Light
{
public:
	AmbientLight() {}
	AmbientLight(glm::vec3 color, float intensity);

	void Update(glm::vec3 color, float intensity) override;
	
	void Bind(Shader& shader);

	glm::vec3 GetColor() override;
	float GetIntensity() override;

private:

	
};

#endif