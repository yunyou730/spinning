#pragma once

#include "ManagerBase.h"
#include <map>
#include <vector>
#include <functional>
#include "Delegate.h"

/*
@TODO shall remove, event declarations shall put into EventDefine.h.cpp
*/
namespace ayy
{
class Game;
class EventManager : public ManagerBase,public IManagerNeedInit<>
{
public:
	EventManager();
	virtual ~EventManager();	
	virtual void Init() override;
};
}
