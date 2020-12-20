#pragma once
#include <vector>
#include <map>
#include <unordered_map>

namespace ayy
{
	class ManagerBase;
	class IManagerNeedTick;
	class IManagerNeedDraw;

	class Game
	{
	public:
		Game();
		~Game();

		void Init();

		void UpdateFrame();
		void DrawFrame();
		
		template<typename TManager>
		TManager* GetManager()
		{
			auto it = _allManagers.find(typeid(TManager).hash_code());
			return it != _allManagers.end() ? dynamic_cast<TManager*>(it->second) : nullptr;
		}

	protected:
		
		void Clean();

		void RegisterManagers();

		template<typename TManager,typename... TArgs>
		TManager* RegisterManager(TArgs... args);

	protected:
		std::vector<IManagerNeedTick*>				_tickManagers;
		std::vector<IManagerNeedDraw*>				_drawManagers;
		std::unordered_map<size_t, ManagerBase*>	_allManagers;
	};
}
