#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include <pch.h>

template <typename TN>
struct Identity { typedef TN type; };

struct VertexElementLayout
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(float);

		case GL_BYTE:
			return sizeof(char);

		case GL_INT:
			return sizeof(int);
			
		default:
			return 0;
		}
	}
};

class VertexBuffer
{
public:
	inline VertexBuffer() : m_Stride(0) { glGenBuffers(1, &m_VBO); }
	VertexBuffer(const std::vector<GLfloat>& vertices,  GLenum drawType);
	~VertexBuffer();
	void AddData(const std::vector<GLfloat>& vertices,  GLenum drawType);

	inline void Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_VBO); EnableLayouts(); }
	inline void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	template<typename T>
	void PushLayout(unsigned int count)
	{
		PushLayout(count, Identity<T>());
	}

	void EnableLayouts();

private:
	template<typename TN>
	void PushLayout(unsigned int count, Identity<TN>)
	{
		std::cout << "Bad layout pushed!" << std::endl;
	}
	void PushLayout(unsigned int count, Identity<float>)
	{
		m_AttributePointer.push_back({ GL_FLOAT, count, false });
		m_Stride += sizeof(float) * count;
	}
	void PushLayout(unsigned int count, Identity<int>)
	{
		m_AttributePointer.push_back({ GL_INT, count, false });
		m_Stride += sizeof(int) * count;
	}
	void PushLayout(unsigned int count, Identity<char>)
	{
		m_AttributePointer.push_back({ GL_BYTE, count, true });
		m_Stride += sizeof(char) * count;
	}


private:
	unsigned int m_VBO;
	unsigned int m_Stride;
	std::vector<VertexElementLayout> m_AttributePointer;
};

#endif