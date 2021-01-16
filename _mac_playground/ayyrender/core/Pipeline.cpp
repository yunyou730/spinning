#include "Pipeline.h"

AYY_NS_BEGIN
Pipeline::Pipeline(int viewportWidth,int viewportHeight)
{
    _camera = new Camera(viewportWidth,viewportHeight);
}

Pipeline::~Pipeline()
{
    SAFE_DELETE(_camera);
    SAFE_DELETE(_frameBuffer);
    SAFE_DELETE(_zBuffer);
}

AYY_NS_END
