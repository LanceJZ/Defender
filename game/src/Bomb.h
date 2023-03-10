#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Timer.h"

class Bomb : public Model3D
{
public:
	Bomb();
	virtual ~Bomb();

	void SetModel(Model model, Texture2D texture);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	Timer* LifeTimer = new Timer();
	Model3D MirrorR;
	Model3D MirrorL;

	void MirrorUpdate();

};