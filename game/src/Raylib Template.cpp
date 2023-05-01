#pragma warning ( push )
#pragma warning ( disable : 26495 )

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Game.h"

#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
	#define DBG_NEW new
#endif

int main()
{
	Game *game = DBG_NEW Game();

	game->Initialize();
	game->Load();
	game->BeginRun();
	game->GameLoop();

	delete game;

	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
	_CrtDumpMemoryLeaks();
}

#pragma warning ( pop )