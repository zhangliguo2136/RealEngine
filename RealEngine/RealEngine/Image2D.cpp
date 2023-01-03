#include "Image2D.h"

#include "TextureGLCache.h"
#include "RenderSystem.h"
#include "RenderTextureCmd.h"

Image2D::Image2D(std::string filename)
{
	m_filename = filename;
}

Image2D::~Image2D()
{
}

void Image2D::LoadImageFormFile(std::string filename)
{
	m_filename = filename;
}

void Image2D::onDraw()
{
	std::shared_ptr<RenderTextureCmd> cmd = std::make_shared<RenderTextureCmd>();
	cmd->position = this->getPosition();
	cmd->size = this->getSize();
	cmd->rotate = this->getRotation();
	cmd->scale = this->getScale();
	cmd->glTextureID = TextureGLCache::getInstance().findOrCreate(m_filename)->getTextureID();

	auto& renderSys = RenderSystem::getInstance();
	renderSys.AddCommand(cmd);
}