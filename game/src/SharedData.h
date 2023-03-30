#pragma once
#include "Common.h"

class SharedData : Common
{
public:
	bool LandersMutantsBeGone = false;
	bool PodsSwarmersBeGone = true;
	bool BombersBeGone = true;
	bool PeopleBeGone = false;
	int Wave = 0;


	bool Initialize();
	bool BeginRun();

};

