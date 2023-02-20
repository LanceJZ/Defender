#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"

class Lander : public Model3D
{
public:


	Lander();
	virtual ~Lander();

	EnemyShot Shot;

	void SetShotModel(Model model, Texture2D texture);
	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
};

