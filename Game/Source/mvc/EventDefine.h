#include "../Delegate.h"

class Game;
namespace ayy
{
	class Node;
	struct EventDefine
	{
		static Delegate<> EVT_TEST_1;
		static Delegate<Game*>	EVT_GAME_LAUNCHED;
		static Delegate<Node*>	EVT_ADD_DRAW_NODE;
	};

}