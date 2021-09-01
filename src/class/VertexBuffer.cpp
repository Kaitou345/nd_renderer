#include <pch.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const std::vector<GLfloat>& vertices,  GLenum drawType) : m_Stride(0)
{
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]) , vertices.data(), drawType);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VBO);
}

void VertexBuffer::AddData(const std::vector<GLfloat>& vertices,  GLenum drawType)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]) , vertices.data(), drawType);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::EnableLayouts()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	
	unsigned int offset = 0;
	for (size_t i = 0; i < m_AttributePointer.size(); i++)
	{
		const auto& k = m_AttributePointer[i];

		glVertexAttribPointer(i, k.count, k.type, k.normalized, m_Stride, (const void*) offset);
		glEnableVertexAttribArray(i);

		offset += k.count * VertexElementLayout::GetSize(k.type);
	}
}
