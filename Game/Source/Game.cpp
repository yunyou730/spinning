#include "Game.h"
#include "Global.h"
#include "ManagerBase.h"
#include "RenderManager.h"
#include "EventManager.h"
#include <stdexcept>
#include "WorkflowManager.h"

namespace ayy
{
Game::Game()
{
	
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
		delete it.second;
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
	RegisterManager<EventManager>();
	RegisterManager<WorkflowManager>();
}

template<typename TManager, typename... TArgs>
TManager* Game::RegisterManager(TArgs... args)
{
	auto it = _allManagers.find(typeid(TManager).hash_code());
	if (it != _allManagers.end())
	{
		std::string msg = std::string("Register same manager : ") + typeid(TManager).name();
		throw std::runtime_error(msg);
	}

	TManager* manager = new TManager();
	_allManagers[typeid(TManager).hash_code()] = manager;

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

	typeid(manager);
	return manager;
}

}
