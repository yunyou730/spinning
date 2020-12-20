#pragma once
#include "ManagerBase.h"
#include <SDL.h>
#include "utils/Vector.hpp"
#include <list>

namespace ayy
{
	class Node;
	class RenderManager : public ManagerBase,
						  public IManagerNeedInit<SDL_Renderer*,const Vector4<Uint8>&>,
						  public IManagerNeedDraw
	{
	public:
		RenderManager();
		~RenderManager();
		virtual void Init(SDL_Renderer* renderer,const Vector4<Uint8>& clearColor) override;
		virtual void DrawFrame() override;

	private:
		inline void ClearFrame();
		inline void PresentFrame();

		void DrawEachNode(Node* node);

		bool OnAddNode(Node* node);
		bool OnRemoveNode(Node* node);

	protected:
		SDL_Renderer*	_frameRenderer = nullptr;
		Vector4<Uint8>	_clearColor;

		std::list<Node*>		_toDraw;
	};
}
