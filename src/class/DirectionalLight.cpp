#include <pch.h>
#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity)
{
    m_Color = color;
    m_Direction = direction;
    m_Intensity = intensity;
}

void DirectionalLight::Update(glm::vec3 color, glm::vec3 direction, float intensity)
{
    m_Color = color;
    m_Direction = direction;
    m_Intensity = intensity;
}

void DirectionalLight::Bind(Shader& shader)
{
    shader.SetUniform3fv("directionalLight.base.Color", m_Color);
    shader.SetUniform1f("directionalLight.base.Intensity", m_Intensity);
    shader.SetUniform3fv("directionalLight.Direction", m_Direction);
}

glm::vec3 DirectionalLight::GetColor()
{
    return m_Color;
}

glm::vec3 DirectionalLight::GetDirection()
{
    return m_Direction;
}

float DirectionalLight::GetIntensity()
{
    return m_Intensity;
}
