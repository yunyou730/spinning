#pragma once
#include <memory>
#include <stdexcept>

namespace ayy
{
	class XApplication;

	struct Global
	{
		inline static std::shared_ptr<XApplication> SharedApp() {
			if (s_app == nullptr)
			{
				throw std::runtime_error("app is nullptr");
			}
			return s_app;
		}
	
		static void RegisterApp(std::shared_ptr<XApplication> app)
		{
			if (s_app != nullptr)
			{
				throw std::runtime_error("app register to global more than one time");
			}
			s_app = app;
		}		

		static std::shared_ptr<XApplication> s_app;
	};
}
