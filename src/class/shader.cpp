#include <pch.h>
#include "shader.h"

Shader::Shader()
{
	m_ShaderId = glCreateProgram();
}

Shader::Shader(const char* vertPath, const char* fragPath)
{
	// Lines that only belong in constructor -- reference code
	m_ShaderId = glCreateProgram();

	
	ShaderSource shaderSource = ParseShader(vertPath, fragPath);

	if (shaderSource.Vertex.size() == 0 || shaderSource.Fragment.size() == 0)
		std::cout << "Shader missing: " << ((shaderSource.Vertex.size() == 0) ? "vertex shader" : "fragment shader") << std::endl;

	glUseProgram(m_ShaderId);
	AttachShader(shaderSource.Vertex, GL_VERTEX_SHADER);
	AttachShader(shaderSource.Fragment, GL_FRAGMENT_SHADER);

	glLinkProgram(m_ShaderId);

	int result;
	glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &result);
	if (!result)
	{
		int size;
		glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &size);
		char* message = new char[size];
		glGetProgramInfoLog(m_ShaderId, size, &size, message);
		std::cout << message << std::endl;
		delete[] message;
	}

	glValidateProgram(m_ShaderId);
	glGetProgramiv(m_ShaderId, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		int size;
		glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &size);
		char* message = new char[size];
		glGetProgramInfoLog(m_ShaderId, size, &size, message);
		std::cout << "Shader error: " << message << std::endl;
		delete[] message;
	}

	glUseProgram(0);

}

Shader::~Shader()
{
}

void Shader::Bind() const
{
	glUseProgram(m_ShaderId);

}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetProjMatrix(const glm::mat4 matrix)
{
	SetUniformMat4("u_Proj", matrix);
}

void Shader::SetViewMatrix(const glm::mat4 matrix)
{
	SetUniformMat4("u_View", matrix);
}

void Shader::SetModelMatrix(const glm::mat4 matrix)
{
	SetUniformMat4("u_Model", matrix);
}

void Shader::SetUniformMat4(const char* uniform, const glm::mat4 matrix)
{
	glUseProgram(m_ShaderId);

	auto loc = GetUniformLocation(uniform);

	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniform1i(const char* uniform, int value)
{
	glUseProgram(m_ShaderId);

	auto loc = GetUniformLocation(uniform);
	
	glUniform1i(loc, value);
}

void Shader::SetUniform1f(const char* uniform, float value)
{
	auto loc = GetUniformLocation(uniform);
	glUniform1f(loc, value);
}

void Shader::SetUniform3fv(const char* uniform, glm::vec3 value)
{
	auto loc =  GetUniformLocation(uniform);
	glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::AddData(const char* vertPath, const char* fragPath)
{

	ShaderSource shaderSource = ParseShader(vertPath, fragPath);

	glUseProgram(m_ShaderId);
	AttachShader(shaderSource.Vertex, GL_VERTEX_SHADER);
	AttachShader(shaderSource.Fragment, GL_FRAGMENT_SHADER);

	glLinkProgram(m_ShaderId);

	int result;
	glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &result);
	if (!result)
	{
		int size;
		glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &size);
		char* message = new char[size];
		glGetProgramInfoLog(m_ShaderId, size, &size, message);
		std::cout << message << std::endl;
	}

	glValidateProgram(m_ShaderId);
	glGetProgramiv(m_ShaderId, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		int size;
		glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &size);
		char* message = new char[size];
		glGetProgramInfoLog(m_ShaderId, size, &size, message);
		std::cout << "Shader error: " << message << std::endl;
	}

	glUseProgram(0);
}

ShaderSource Shader::ParseShader(const char* vertPath, const char* fragPath)
{
	std::fstream vertFile(vertPath);
	std::fstream fragFile(fragPath);

	std::stringstream vertStream;
	std::stringstream fragStream;

	std::string line;
	while (std::getline(vertFile, line))
	{
		vertStream << line << '\n';
	}

	line = "";

	while (std::getline(fragFile, line))
	{
		fragStream << line << '\n';
	}

	return { vertStream.str(), fragStream.str() };
}

void Shader::AttachShader(std::string shaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	const char* source = shaderSource.c_str();
	const GLint size = shaderSource.size();

	glShaderSource(shader, 1, &source, &size);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		char* message = new char[logLength];

		glGetShaderInfoLog(shader, logLength, &logLength, message);
		std::cout << message << std::endl;

		delete[] message;
	}

	glAttachShader(m_ShaderId, shader);

}

int Shader::GetUniformLocation(const char* uniform)
{

	if (m_uniformCache.find(uniform) != m_uniformCache.end())
		return m_uniformCache[uniform];
	
	auto location = glGetUniformLocation(m_ShaderId, uniform);

	if (location == -1)
		std::cout << "Uniform not found: " << uniform << std::endl;

	m_uniformCache[uniform] = location;

	return location;
}
