#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Timer.h"

class EnemyShot : public Model3D
{
public:
	virtual ~EnemyShot();

	void SetModel(Model model, Texture2D texture);
	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position, Vector3 velocity, float life);

private:
	Model MirrorR = { 0 };
	Model MirrorL = { 0 };
	Timer* LifeTimer = new Timer();

	void DrawMirror();
};