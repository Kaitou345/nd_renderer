#include <pch.h>
#include "VertexArray.h"

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VAO);
}
