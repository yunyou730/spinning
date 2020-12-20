#include "EventDefine.h"
#include "../renderer/Node.h"

namespace ayy
{
	Delegate<> EventDefine::EVT_TEST_1;
	Delegate<Game*>	EventDefine::EVT_GAME_LAUNCHED;
	Delegate<Node*>	EventDefine::EVT_ADD_DRAW_NODE;
}
