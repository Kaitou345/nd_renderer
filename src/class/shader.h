#ifndef SHADER
#define SHADER

#include <pch.h>

struct ShaderSource
{ 
	std::string Vertex, Fragment;
};

class Shader
{
public:
	Shader();
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	void AddData(const char* vertPath, const char* fragPath);

	void Bind() const ;
	void Unbind() const;
	
	void SetProjMatrix(const glm::mat4 matrix);
	void SetViewMatrix(const glm::mat4 matrix);
	void SetModelMatrix(const glm::mat4 matrix);

	void SetUniformMat4(const char* uniform,const glm::mat4 matrix);
	void SetUniform1i(const char* uniform, int value);
	void SetUniform1f(const char* uniform, float value);
	void SetUniform3fv(const char* uniform, glm::vec3 value);

private:
	ShaderSource ParseShader(const char* vertPath, const char* fragPath);
	void AttachShader(std::string shaderSource, GLenum shaderType);

	int GetUniformLocation(const char* uniform);

public:
	unsigned int m_ShaderId;
	std::unordered_map<const char*, int> m_uniformCache;
};

#endif