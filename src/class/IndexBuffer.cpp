#include <pch.h>
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const std::vector<GLuint> indices, GLenum drawType) : m_Count(indices.size())
{
	glGenBuffers(1, &m_IBO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), drawType);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_IBO);
}

void IndexBuffer::AddData(const std::vector<GLuint> indices, GLenum drawType)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), drawType);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_Count = indices.size();
}