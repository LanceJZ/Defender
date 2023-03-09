#pragma once
#include "raylib.h"

class BomberControl
{
public:
	BomberControl();
	virtual ~BomberControl();

	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:

};

