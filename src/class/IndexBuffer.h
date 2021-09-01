#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include <pch.h>


class IndexBuffer
{
public:
	inline IndexBuffer() : m_Count(0) { glGenBuffers(1, &m_IBO); }
	IndexBuffer(const std::vector<GLuint> indices, GLenum drawType);
	~IndexBuffer();
	void AddData(const std::vector<GLuint> indices, GLenum drawType);

	inline void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO); }
	inline void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	inline unsigned int Count() { return m_Count; }

private:
	unsigned int m_IBO;
	unsigned int m_Count;
};

#endif