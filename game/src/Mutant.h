#pragma once
#include "Model3D.h"
#include "EnemyShot.h"
#include "EnemyRadar.h"
#include "EnemyMirror.h"
#include "Player.h"
#include "Timer.h"

class Mutant : public Model3D
{
public:
	Mutant();
	virtual ~Mutant();

	EnemyShot* Shots[4];

	void SetShotModel(Model model);
	void SetRadarModel(Model model);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	bool GotNearPlayer = false;
	bool BackToToporBottom = false;
	float Speed = 100;

	EnemyRadar Radar;
	EnemyMirror Mirror;
	Player* ThePlayer = nullptr;
	Timer* ShotTimer = new Timer();
	Timer* ChangeSpeedTimer = new Timer();

	void FireShot();
	void ChasePlayer();
	void ResetChase();
};