#pragma once

#include "ManagerBase.h"
#include <map>
#include <vector>
#include <functional>

namespace ayy
{




class EventManager : public ManagerBase,public IManagerNeedInit<>
{
public:
	using EventType = size_t;

	EventManager();
	virtual ~EventManager();
	
	virtual void Init() override;

	template<typename... TArgs>
	void RegisterEvent(EventType eventType)
	{
		
	}

	template<typename... TArgs>
	void MapEvent(EventType eventType, const std::function<void(TArgs... args)>& func)
	{
		
	}

	template<typename... TArgs>
	void UnMapEvent(EventType eventType, const std::function<void(TArgs... args)>& func)
	{
	
	}

protected:
	
};



}
