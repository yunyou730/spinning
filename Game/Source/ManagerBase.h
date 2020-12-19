#pragma once

namespace ayy
{
	class ManagerBase
	{
	public:
		virtual ~ManagerBase() {}
	};

	class IManagerNeedTick
	{
	public:
		virtual void UpdateFrame() = 0;
	};

	template<typename... TArgs>
	class IManagerNeedInit
	{
	public:
		virtual void Init(TArgs... args) = 0;
	};

	class IManagerNeedDraw
	{
	public:
		virtual void DrawFrame() = 0;
	};
}
