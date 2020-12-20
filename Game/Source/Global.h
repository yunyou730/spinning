#pragma once
#include <memory>
#include <stdexcept>
#include "XApplication.h"
#include "Game.h"

namespace ayy
{
	class XApplication;
	class Game;
	class EventManager;

	struct Global
	{
		inline static std::shared_ptr<XApplication> SharedApp() 
		{
			if (s_app == nullptr)
			{
				throw std::runtime_error("app is nullptr");
			}
			return s_app;
		}

		inline static std::shared_ptr<Game>& SharedGame()
		{
			return SharedApp()->GetGame();
		}

		inline static SDL_Renderer* GetFrameRenderer()
		{
			return SharedApp()->GetRenderer();
		}

		static void RegisterApp(std::shared_ptr<XApplication> app)
		{
			if (s_app != nullptr)
			{
				throw std::runtime_error("app register to global more than one time");
			}
			s_app = app;
		}		

		static std::shared_ptr<XApplication> s_app;
	};
}
