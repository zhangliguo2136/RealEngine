#include "Texture2D.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

Texture2D::Texture2D()
{

}

Texture2D::Texture2D(unsigned char* pData, int width, int height, int nrChannel)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	{
		GLenum format;
		if (nrChannel == 1)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			format = GL_RED;
		}
		else if (nrChannel == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			format = GL_RGB;
		}
		else if (nrChannel == 4)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
	if (m_TextureID >= 0)
	{
		glDeleteTextures(1, &m_TextureID);
		m_TextureID = -1;
	}
}