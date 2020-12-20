#pragma once
#include "ManagerBase.h"

namespace ayy
{
	class WorkflowManager : public ManagerBase,public IManagerNeedInit<>
	{
	public:
		virtual void Init() override;
	};
}
