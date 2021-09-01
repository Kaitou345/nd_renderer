#ifndef TEXTURE
#define TEXTURE

#include <pch.h>
class Texture
{
public:
	Texture();
	Texture(const char* filePath);
	~Texture();

	void AddData(const char* filePath);
	void Bind(unsigned int slot = 0);
	void Unbind();

private:
	unsigned int m_TextureId;
};

#endif