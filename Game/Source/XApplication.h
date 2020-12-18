#pragma once
#include "Application.h"
#include <SDL.h>
#include <string>

namespace ayy
{
	class Game;
	class GUI;
	class XApplication : public Application
	{
	public:
		XApplication(const std::string& title,int screenWidth,int screenHeight);
		virtual ~XApplication();

		virtual bool Prepare() override;
		virtual void MainLoop() override;
		virtual bool Cleanup() override;

	private:
		bool InitSDL();
		void CleanupSDL();
		void HandleSDLEvent();

	private:
		void UpdateFrame(float deltaTime);
		void DrawFrame();

	private:
		int				_screenWidth;
		int				_screenHeight;
		std::string		_title;

		SDL_Window*		_window			= nullptr;
		SDL_Surface*	_screenSurface	= nullptr;
		SDL_Renderer*	_screenRenderer = nullptr;

	private:
		Game*	_game = nullptr;
		GUI*	_gui = nullptr;
	};
}
