#include "RenderManager.h"
#include "mvc/EventDefine.h"
#include <functional>
#include <algorithm>
#include "renderer/Node.h"

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

		std::function<bool(Node*)> funcAddNode = std::bind(&RenderManager::OnAddNode, this, std::placeholders::_1);
		EventDefine::EVT_ADD_DRAW_NODE += funcAddNode;
	}
	
	void RenderManager::DrawFrame()
	{
		ClearFrame();
		for (auto it : _toDraw)
		{
			DrawEachNode(it);
		}
		
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

	void RenderManager::DrawEachNode(Node* node)
	{
		node->Draw(_frameRenderer);
	}

	bool RenderManager::OnAddNode(Node* node)
	{
		_toDraw.push_back(node);
		return true;
	}

	bool RenderManager::OnRemoveNode(Node* node)
	{
		remove_if(_toDraw.begin(), _toDraw.end(), [&](Node* theNode)->bool {
			return node == theNode;
		});
		return true;
	}
}
