#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "EnemyRadar.h"
#include "Player.h"
#include "Timer.h"

class Mutant : public Model3D
{
public:
	Mutant();
	virtual ~Mutant();

	EnemyShot* Shots[4];

	void SetModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	void SetRadarModel(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	bool GotNearPlayer = false;
	float Speed = 100;

	EnemyRadar Radar;
	Model3D MirrorR;
	Model3D MirrorL;
	Player* ThePlayer = nullptr;
	Timer* ShotTimer = new Timer();
	Timer* ChangeSpeedTimer = new Timer();

	void FireShot();
	float AimedShot();
	void MirrorUpdate();
	void ChasePlayer();
};