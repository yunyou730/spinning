#pragma once
#include <SDL.h>

namespace ayy
{
	class GUI
	{
		
	public:
		void Init(SDL_Window* window, const SDL_GLContext& glContext);
		void Cleanup();

		void ProcessEvent(const SDL_Event& e);
	};
}

