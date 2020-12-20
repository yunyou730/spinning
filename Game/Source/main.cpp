#include "Global.h"
#include <SDL.h>
#include "XApplication.h"
#include <memory>
#include "Delegate.h"
#include "EventManager.h"

using namespace ayy;

void Test()
{
	using Delegate1 = ayy::Delegate<int, float>;
	Delegate1 deleg1;
	Delegate1::HandleID h1 = deleg1 += [](int a, float b)->bool {
		printf("[a + b] %f\n", a + b);
		return true;
	};

	auto h2 = deleg1 += [](int a, float b)->bool {
		printf("[a - b] %f\n", a - b);
		return true;
	};

	deleg1.Execute(1, 5.0f);
	if (deleg1 -= h1)
	{
		printf("yyy\n");
	}
	else
	{
		printf("xx\n");
	}

	if (deleg1 -= 339)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
	deleg1.Execute(3, 0.1f);
}

void Test1()
{
	//EventManager::EVT_TEST_1();

}

int main(int, char**)
{
	//Test();
	//Test1();
	
	std::shared_ptr<ayy::XApplication> app = std::make_shared<ayy::XApplication>("XGame",640,480,60);
	ayy::Global::RegisterApp(app);
	app->Prepare();
	app->MainLoop();
	app->Cleanup();
	
	return 0;
}
