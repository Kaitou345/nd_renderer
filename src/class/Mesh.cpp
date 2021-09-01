#include <pch.h>
#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
{
	m_VB.AddData(vertices, GL_STATIC_DRAW);
	m_VB.PushLayout<float>(3);
	m_VB.PushLayout<float>(2);
	m_VB.PushLayout<float>(3);
	m_VB.EnableLayouts();

	m_IB.AddData(indices, GL_STATIC_DRAW);
}

void Mesh::AddData(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
{
	m_VB.AddData(vertices, GL_STATIC_DRAW);
	m_VB.PushLayout<float>(3);
	m_VB.PushLayout<float>(2);
	m_VB.PushLayout<float>(3);
	m_VB.EnableLayouts();

	m_IB.AddData(indices, GL_STATIC_DRAW);
}

void Mesh::RenderMesh(const Shader& shader)
{
	shader.Bind();
	Bind();
	glDrawElements(GL_TRIANGLES, GetIndexCount(), GL_UNSIGNED_INT, 0);
}