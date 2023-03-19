#pragma once
#include "Model3D.h"
#include "EnemyShot.h"
#include "EnemyRadarMirror.h"
#include "Player.h"
#include "Timer.h"

class Mutant : public Model3D
{
public:
	bool CountChange = false;

	Mutant();
	virtual ~Mutant();

	EnemyShot* Shots[4];

	bool Initialize();
	void SetShotModel(Model model);
	void SetRadarModel(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	bool GotNearPlayer = false;
	bool BackToToporBottom = false;
	float Speed = 100;

	EnemyRadarMirror RadarMirror;
	Player* ThePlayer = nullptr;
	Timer ShotTimer;
	Timer ChangeSpeedTimer;

	void FireShot();
	void ChasePlayer();
	void CheckCollision();
	void Destroy();
};