#include "Node.h"

namespace ayy
{
	Node::Node()
	{
	
	}
	
	Node::~Node()
	{
		
	}

	void Node::SetWorldPosition(float x, float y)
	{
		_worldPos.x = x;
		_worldPos.y = y;
	}

	void Node::SetAnchor(float x, float y)
	{
		_anchor.x = x;
		_anchor.y = y;
	}

	bool Node::Draw(SDL_Renderer* renderer)
	{
		if (!IsVisible())
			return false;
		return true;
	}
}

