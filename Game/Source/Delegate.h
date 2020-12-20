#pragma once
#include "ManagerBase.h"
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>

namespace ayy
{
	template<typename... TArgs>
	class Delegate
	{
	public:
		using HandleID = size_t;
		using FuncProto = std::function<bool(TArgs... args)>;

	protected:
		struct Callback
		{
			HandleID id;
			FuncProto func;

			Callback(HandleID id, const FuncProto& func)
			{
				this->id = id;
				this->func = func;
			}

			~Callback()
			{
				printf("~Delegate::Callback) %zu\n",id);
			}
		};

	public:
		size_t Bind(const FuncProto& func)
		{
			HandleID nextID = ++_handleCounter;
			_callbackMap[nextID] = std::make_shared<Callback>(nextID, func);
			return nextID;
		}

		bool Cancel(const HandleID& handleID)
		{
			auto it = _callbackMap.find(handleID);
			if (it != _callbackMap.end())
			{
				_callbackMap.erase(it);
				return true;
			}
			return false;
		}
		
		void Execute(TArgs... args)
		{
			for(auto it : _callbackMap)
			{
				it.second->func(args...);
			}
		}

		HandleID operator += (const FuncProto& func)
		{
			return Bind(func);
		}

		bool operator -= (HandleID handleID)
		{
			return Cancel(handleID);
		}

		void operator ()(TArgs... args)
		{
			Execute(args...);
		}

	protected:
		std::map<HandleID,std::shared_ptr<Callback>>	_callbackMap;
		HandleID										_handleCounter = 0;
	};
}
