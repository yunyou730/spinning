#include "RenderManager.h"

namespace ayy
{
	RenderManager::RenderManager()
	{
	
	}

	RenderManager::~RenderManager()
	{
		
	}

	void RenderManager::Init(SDL_Renderer* renderer, const Vector4<Uint8>& clearColor)
	{
		_frameRenderer	= renderer;
		_clearColor		= clearColor;
	}
	
	void RenderManager::DrawFrame()
	{
		ClearFrame();
		// @miao @todo
		// do draw ...
		PresentFrame();
	}

	void RenderManager::ClearFrame()
	{
		SDL_SetRenderDrawColor(_frameRenderer, _clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
		SDL_RenderClear(_frameRenderer);
	}

	void RenderManager::PresentFrame()
	{
		SDL_RenderPresent(_frameRenderer);
	}
}
