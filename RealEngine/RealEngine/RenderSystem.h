#pragma once

#include <memory>

#include "RenderQueue.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	static RenderSystem& getInstance()
	{
		static RenderSystem instance;
		return instance;
	}

	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator = (const RenderSystem&) = delete;

public:
	void Tick();

	void AddCommand(std::shared_ptr<RenderCommand>);

private:
	RenderQueue* _renderQueue;
};