#ifndef MATERIAL
#define MATERIAL

#include <pch.h>


class Material
{
public:
	Material() = default;
	Material(float specularIntensity, float specularExponent)
		: m_SpecularIntensity(specularIntensity), m_SpecularExponent(specularExponent) {}
	
	float GetSpecularIntensity() { return  m_SpecularIntensity; }
	float GetSpecularExponent() { return m_SpecularExponent; }


private:
	float m_SpecularIntensity;
	float m_SpecularExponent;
};

#endif