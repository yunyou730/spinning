#pragma once
#include "Node.h"
#include "../utils/Vector.hpp"

namespace ayy
{
	class RectNode : public Node
	{
	public:
		static RectNode* Create(const Vector2<float>& size);

		virtual bool Draw(SDL_Renderer* renderer) override;
		
		void SetSize(const Vector2<float>& size) { _size = size; }

	private:
		RectNode();
	
	protected:
		Vector2<float>		_size;
	};
}
