#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "Timer.h"

class Lander : public Model3D
{
public:


	Lander();
	virtual ~Lander();

	EnemyShot* Shots[4];

	void SetShotModel(Model model, Texture2D texture);
	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	bool PickUpMode = false;
	bool GoingDownForPickupMode = false;
	bool SeekMode = true;
	float GroundHoverY = 0;
	Timer* ShotTimer;
	Model MirrorR;
	Model MirrorL;
	Model ShotMirrorR;
	Model ShotMirrorL;

	void FireShot();
	void FireShots();
};

