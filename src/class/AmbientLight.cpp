#include <pch.h>

#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 color, float intensity)
{
    m_Color = color;
    m_Intensity = intensity;
}

void AmbientLight::Update(glm::vec3 color, float intensity)
{
    m_Color = color;
    m_Intensity = intensity;
}

void AmbientLight::Bind(Shader& shader)
{
    shader.Bind();
    shader.SetUniform3fv("ambientLight.base.Color", m_Color);
    shader.SetUniform1f("ambientLight.base.Intensity", m_Intensity);
}

glm::vec3 AmbientLight::GetColor()
{
    return m_Color;
}

float AmbientLight::GetIntensity()
{
    return m_Intensity;
}
