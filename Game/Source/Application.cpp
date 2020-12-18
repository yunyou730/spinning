#include "Application.h"

namespace ayy
{
	Application::Application()
	{

	}

	Application::~Application()
	{
		Cleanup();
	}

	bool Application::Prepare()
	{
		if (_hasPrepared)
		{
			return false;
		}
		_hasPrepared = true;
		_hasCleaned = false;

		return true;
	}

	bool Application::Cleanup()
	{
		if (_hasCleaned) 
		{
			return false;
		}
		_hasCleaned = true;
		_hasPrepared = false;

		return true;
	}
}
