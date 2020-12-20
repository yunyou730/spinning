#include "XApplication.h"
#include <stdexcept>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include <GL/gl3w.h>

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

	
	// GL 3.0 + GLSL 130
	//const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	if (!InitSDL())
	{
		return false;
	}
	InitGLContext();

	SetTargetFPS(_targetFPS);

	_game = std::make_shared<ayy::Game>();
	_game->Init();

	_gui = std::make_shared<ayy::GUI>();
	_gui->Init(_window,_glContext);

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

	_gui->Cleanup();

	SDL_GL_DeleteContext(_glContext);

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

		// Create window with graphics context
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

		_window = SDL_CreateWindow(_title.c_str(), 
									SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, 
									_screenWidth, 
									_screenHeight,
									window_flags);

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

void XApplication::InitGLContext()
{
	_glContext = SDL_GL_CreateContext(_window);
	SDL_GL_MakeCurrent(_window, _glContext);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	gl3wInit();
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
		_gui->ProcessEvent(e);
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
