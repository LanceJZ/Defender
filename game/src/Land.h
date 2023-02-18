#pragma once
#include "raylib.h"
#include "Model3D.h"

class Land
{
public:
	Model3D* LandParts[9];

	Land();
	virtual ~Land();

	virtual void Load();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:

};

