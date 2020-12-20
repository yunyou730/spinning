#include "RectNode.h"

namespace ayy
{
	using Super = Node;
	
	RectNode::RectNode()
	{

	}

	RectNode* RectNode::Create(const Vector2<float>& size)
	{
		RectNode* node = new RectNode();
		node->SetSize(size);
		return node;
	}

	bool RectNode::Draw(SDL_Renderer* renderer)
	{
		if (!Super::Draw(renderer))
		{
			return false;
		}
		
		SDL_Rect rect = { _worldPos.x ,_worldPos.y,_size.x,_size.y };
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
		SDL_RenderFillRect(renderer, &rect);

		return true;
	}

	void SetSize(const Vector2<float>& size)
	{
		
	}
}

