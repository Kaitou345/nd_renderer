#ifndef MESH
#define MESH

#include <pch.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "shader.h"

class Mesh
{
public:
	inline Mesh() = default;
	Mesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void AddData(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	inline unsigned int GetIndexCount() { return m_IB.Count(); }
	inline void Bind()
	{
		m_VB.Bind();
		m_IB.Bind();
		m_VB.EnableLayouts();
	}

	void RenderMesh(const Shader& shader);

private:
	VertexBuffer m_VB;
	IndexBuffer m_IB;

};

#endif