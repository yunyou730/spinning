#include <stdio.h>
#include "../core/AppFramework.h"
#include "Testcase.h"

using namespace ayy;

int main( int argc, char* args[] )
{
    Testcase testcase;
    AppFramework app(800,800);
    app.RegisterUpdateFunc(std::bind(&Testcase::Update,&testcase,std::placeholders::_1,std::placeholders::_2));
    app.RegisterDrawFunc(std::bind(&Testcase::Draw,&testcase,std::placeholders::_1));
    app.MainLoop();
    app.Clean();
    return 0;
}
