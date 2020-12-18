#include "Global.h"
#include "XApplication.h"
#include <memory>

int main(int, char**)
{
	std::shared_ptr<ayy::XApplication> app = std::make_shared<ayy::XApplication>("XGame",640,480,60);
	ayy::Global::RegisterApp(app);
	app->Prepare();
	app->MainLoop();
	app->Cleanup();
	return 0;
}
