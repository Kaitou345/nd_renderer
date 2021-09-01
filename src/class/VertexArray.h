#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include <pch.h>

class VertexArray
{
public:
	inline VertexArray() { glGenVertexArrays(1, &m_VAO); }
	~VertexArray();

	inline void Bind() { glBindVertexArray(m_VAO); }
	inline void Unbind() { glBindVertexArray(0); }

private:
	unsigned int m_VAO;
};

#endif