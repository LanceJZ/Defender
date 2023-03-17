#pragma once
#include "Common.h"

class SharedData : Common
{
public:
	SharedData();
	virtual ~SharedData();

	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:

};

