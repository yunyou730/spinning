#pragma once
#include <vector>

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

		void UpdateFrame();
		void DrawFrame();

	protected:
		void Init();
		void Clean();

		void RegisterManagers();

		template<typename TManager,typename... TArgs>
		void RegisterManager(TArgs... args);


	protected:
		std::vector<IManagerNeedTick*>	_tickManagers;
		std::vector<IManagerNeedDraw*>	_drawManagers;
		std::vector< ManagerBase*>		_allManagers;
	};
}
