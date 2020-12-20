#pragma once
#include "ManagerBase.h"

namespace ayy
{
	class RenderManager;
	class WorkflowManager : public ManagerBase,public IManagerNeedInit<>
	{
	public:
		virtual void Init() override;

	protected:
		void TestDraw();

	protected:
		//RenderManager* _rm;
	};
}
