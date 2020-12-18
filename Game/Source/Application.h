#pragma once

namespace ayy
{
	class Application
	{
	public:
		virtual ~Application();

		virtual bool Prepare();
		virtual void MainLoop() = 0;
		virtual bool Cleanup();

	protected:
		Application();
		inline bool ShallQuit() const { return _bShallQuit; }

	protected:

		bool	_bShallQuit		= false;
		bool	_hasPrepared	= false;
		bool	_hasCleaned		= false;
	};
}
