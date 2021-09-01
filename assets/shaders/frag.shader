#version 330 core

out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D u_textureId;

struct Light
{
	vec3 Color;
	float Intensity;
};

struct AmbientLight
{
	Light base;
};

struct DirectionalLight
{
	Light base;
	vec3 Direction;
};

uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;

uniform float u_SpecularIntensity;
uniform float u_SpecularExponent;

uniform vec3 u_CameraPos;

vec4 CalculateLightByDirection(Light light, vec3 direction)
{
	float diffuseFactor = max(dot(normalize(v_Normal), normalize(direction)), 0.f);
	vec4 DiffuseColor = vec4(light.Color * light.Intensity * diffuseFactor, 1.0f);

	// Specular calculations
	float specularFactor;
	vec4 specularColor = vec4(0.f, 0.f, 0.f, 0.f);

	if (diffuseFactor > 0.f)
	{
		vec3 fragToCam = normalize(u_CameraPos - v_FragPos);

		vec3 reflectionVector = normalize(reflect(direction, v_Normal));

		specularFactor = max(dot(fragToCam, reflectionVector), 0.f);
		if (specularFactor > 0.f)
		{
			specularFactor = pow(specularFactor, u_SpecularExponent);
			specularColor = vec4(light.Color * specularFactor * u_SpecularIntensity, 1.f);
		}
	}

	return (specularColor + DiffuseColor);
}

vec4 CalculateDirectionalLight()
{
	return CalculateLightByDirection(directionalLight.base, directionalLight.Direction);
}

void main()
{

	// Ambient Light calculations
	vec4 AmbientColor = vec4(ambientLight.base.Color, 1.0f) * ambientLight.base.Intensity;

	vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0) + AmbientColor;

	finalColor += CalculateDirectionalLight();

	color = texture(u_textureId, v_TexCoords) * finalColor;

}