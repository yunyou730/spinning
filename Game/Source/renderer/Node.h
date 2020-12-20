#pragma once
#include <SDL.h>
#include "../utils/Vector.hpp""
#include <vector>

namespace ayy
{
	class Node
	{
	public:
		Node();
		virtual ~Node();
		virtual bool Draw(SDL_Renderer* renderer);

		void SetWorldPosition(float x,float y);
		void SetAnchor(float x,float y);
		void SetVisible(bool bVisible) { _bVisible = bVisible; }
		void SetColor(const Vector4<Uint8>& color) { _color = color; }

		bool IsVisible() const { return _bVisible; }
		int GetPriority() const { return _priority; }

	protected:
		int						_priority = 0;
		bool					_bVisible = true;

		ayy::Vector2<float>		_worldPos;
		ayy::Vector2<float>		_anchor;

		ayy::Vector4<Uint8>		_color;
	};
}
