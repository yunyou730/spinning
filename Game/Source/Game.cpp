#include "Game.h"
#include "Global.h"
#include "ManagerBase.h"
#include "RenderManager.h"

namespace ayy
{
Game::Game()
{
	Init();
}

Game::~Game()
{
	Clean();
}

void Game::Init()
{
	RegisterManagers();
}

void Game::Clean()
{
	for (auto it : _allManagers)
	{
		delete it;
	}
	_allManagers.clear();
	_drawManagers.clear();
	_tickManagers.clear();
}

void Game::UpdateFrame()
{
	for (auto it : _tickManagers)
	{
		it->UpdateFrame();
	}
}

void Game::DrawFrame()
{
	for (auto it : _drawManagers)
	{
		it->DrawFrame();
	}
}

void Game::RegisterManagers()
{
	RegisterManager<RenderManager,SDL_Renderer*,const Vector4<Uint8>&>(
		Global::GetFrameRenderer(),
		Vector4<Uint8>(180,90,64,255)
	);
}

template<typename TManager, typename... TArgs>
void Game::RegisterManager(TArgs... args)
{
	TManager* manager = new TManager();
	_allManagers.push_back(manager);

	IManagerNeedInit<TArgs...>* managerNeedInit = dynamic_cast<IManagerNeedInit<TArgs...>*>(manager);
	if (managerNeedInit != nullptr)
	{
		managerNeedInit->Init(args...);
	}

	IManagerNeedTick* managerNeedTick = dynamic_cast<IManagerNeedTick*>(manager);
	if (managerNeedTick != nullptr)
	{
		_tickManagers.push_back(managerNeedTick);
	}

	IManagerNeedDraw* managerNeedDraw = dynamic_cast<IManagerNeedDraw*>(manager);
	if (managerNeedDraw != nullptr)
	{
		_drawManagers.push_back(managerNeedDraw);
	}
}

}
