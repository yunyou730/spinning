#include "WorkflowManager.h"
#include "Global.h"
#include "Game.h"
#include "EventManager.h"

namespace ayy
{
	void WorkflowManager::Init()
	{
		//auto em = Global::SharedGame()->GetManager<EventManager>();
		Global::SharedGame()->GetManager<EventManager>();
	}
}
