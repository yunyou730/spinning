#include "WorkflowManager.h"
#include "Global.h"
#include "Game.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "renderer/RectNode.h"
#include "mvc/EventDefine.h"

namespace ayy
{
	void WorkflowManager::Init()
	{	
		TestDraw();
	}

	void WorkflowManager::TestDraw()
	{
		RectNode* rect = RectNode::Create(Vector2<float>(80,50));
		rect->SetColor(Vector4<Uint8>(0,0,128,255));
		rect->SetWorldPosition(200, 250);
		EventDefine::EVT_ADD_DRAW_NODE(rect);
	}
}
