#include "XApplication.h"
#include <stdexcept>

namespace ayy
{

using Super = Application;

XApplication::XApplication(const std::string& title,int screenWidth,int screenHeight, int targetFPS)
	:_title(title)
	,_screenWidth(screenWidth)
	,_screenHeight(screenHeight)
{
	printf("Welcome to XGame!\n");
	SetTargetFPS(targetFPS);
}

XApplication::~XApplication()
{
	printf("XGame:Good bye!\n");
}

bool XApplication::Prepare()
{
	if (!Super::Prepare())
	{
		return false;
	}
	if (!InitSDL())
	{
		return false;
	}
	SetTargetFPS(_targetFPS);

	_game	= std::make_shared<ayy::Game>();
	_gui	= std::make_shared<ayy::GUI>();
	return true;
}

void XApplication::MainLoop()
{
	static Uint32 sTimeCounter = SDL_GetTicks();
	while (!ShallQuit())
	{	
		Uint32 now = SDL_GetTicks();
		Uint32 delta = now - sTimeCounter;
		delta = delta <= 1000 ? delta : 1000;
		if (delta >= _targetFrameGap)
		{
			sTimeCounter = now;
			_lastDeltaTime = delta;
			//printf("Do Update At:%d,[delta] %d\n", SDL_GetTicks(), delta);

			HandleSDLEvent();
			UpdateFrame();
			DrawFrame();
		}
	}
}

bool XApplication::Cleanup()
{
	if (!Super::Cleanup())
	{
		return false;
	}	
	CleanupSDL();
	return true;
}

bool XApplication::InitSDL()
{
	do
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::string msg = "SDL Init Error: " + std::string(SDL_GetError());
			throw std::runtime_error(msg);
			break;
		}

		_window = SDL_CreateWindow(_title.c_str(), 
									SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, 
									_screenWidth, 
									_screenHeight,
									SDL_WINDOW_SHOWN);

		if (_window == nullptr)
		{
			std::string msg = "SDL_CreateWindow Error: " + std::string(SDL_GetError());
			throw std::runtime_error(msg);
			break;
		}

		_screenRenderer = SDL_CreateRenderer(_window,-1, SDL_RENDERER_ACCELERATED);
		if (_screenRenderer == nullptr)
		{
			std::string msg = "SDL_CreateRenderer Error: " + std::string(SDL_GetError());
			throw std::runtime_error(msg);
			break;
		}

		_screenSurface = SDL_GetWindowSurface(_window);

		return true;

	} while (0);

	return false;
}

void XApplication::CleanupSDL()
{
	SDL_DestroyWindow(_window);
	_window = nullptr;

	SDL_Quit();
}

void XApplication::HandleSDLEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			_bShallQuit = true;
			break;
		}
	}
}

void XApplication::UpdateFrame()
{
	_game->UpdateFrame();
}

void XApplication::DrawFrame()
{
	_game->DrawFrame();
}

void XApplication::SetTargetFPS(int fps)
{
	_targetFPS = fps;
	_targetFrameGap = 1000 / _targetFPS;
}

int XApplication::GetLastDeltaTime() const
{
	return _lastDeltaTime;
}

}
