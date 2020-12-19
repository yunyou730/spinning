#pragma once
#include "Application.h"
#include <SDL.h>
#include <string>
#include <memory>
#include "Game.h"
#include "GUI.h"

namespace ayy
{
	class XApplication : public Application
	{
	public:
		XApplication(const std::string& title,int screenWidth,int screenHeight,int targetFPS);
		virtual ~XApplication();

		virtual bool Prepare() override;
		virtual void MainLoop() override;
		virtual bool Cleanup() override;

		void SetTargetFPS(int fps);
		int GetLastDeltaTime() const;

		std::shared_ptr<Game>& GetGame() { return _game; }
		SDL_Renderer* GetRenderer() const { return _screenRenderer; }
		
	private:
		bool InitSDL();
		void CleanupSDL();
		void HandleSDLEvent();

	private:
		void UpdateFrame();
		void DrawFrame();
		
	private:
		int				_screenWidth;
		int				_screenHeight;
		std::string		_title;

		SDL_Window*		_window			= nullptr;
		SDL_Surface*	_screenSurface	= nullptr;
		SDL_Renderer*	_screenRenderer = nullptr;

	private:
		int				_targetFPS;
		int				_targetFrameGap;
		int				_lastDeltaTime = 0;

	private:
		std::shared_ptr<Game>	_game	= nullptr;
		std::shared_ptr<GUI>	_gui	= nullptr;
	};
}
