#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "Timer.h"
#include "Player.h"

class Lander : public Model3D
{
public:


	Lander();
	virtual ~Lander();

	EnemyShot* Shots[4];

	void SetModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	bool PickUpMode = false;
	bool GoingDownForPickupMode = false;
	bool SeekMode = false;
	float GroundHoverY = 0;
	Timer* ShotTimer;
	Model MirrorR;
	Model MirrorL;
	Player* ThePlayer;

	void FireShot();
	void FireShots();
	float AimedShot();
};

