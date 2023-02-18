#pragma once
#include "Model3D.h"

class PlayerShot : public Model3D
{
public:
	PlayerShot();
	virtual ~PlayerShot();

	bool Initialize();
	virtual void Load();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:

};

