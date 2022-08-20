#include "Image2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "RenderSystem.h"
#include "RenderTextureCmd.h"

#include <memory>

Image2D::Image2D(std::string filename)
{
	m_filename = filename;
	m_pData = stbi_load(filename.c_str(), &width, &height, &nrChannel, 0);

	if (!m_pData)
	{
		printf("Image2D::failed to load at file: %s\n", filename.c_str());
		return;
	}

	m_Texture = new Texture2D(m_pData, width, height, nrChannel);
}

Image2D::~Image2D()
{
	if (m_pData)
	{
		stbi_image_free(m_pData);
		m_pData = nullptr;
	}

	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
}

void Image2D::onDraw()
{
	std::shared_ptr<RenderTextureCmd> cmd = std::make_shared<RenderTextureCmd>();
	cmd->position = this->getPosition();
	cmd->size = this->getSize();
	cmd->rotate = this->getRotation();
	cmd->scale = this->getScale();
	cmd->texture = m_Texture;

	auto& renderSys = RenderSystem::getInstance();
	renderSys.AddCommand(cmd);
}