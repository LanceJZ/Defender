#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "EnemyRadarMirror.h"
#include "Timer.h"

class Swarmer : public Model3D
{
public:
	Swarmer();
	virtual ~Swarmer();

	EnemyShot* Shots[4];

	bool Initialize();
	void SetShotModel(Model model);
	void SetRadar(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, Vector3 velocity);

private:
	float XVolocity = 0;
	float YVolocity = 0;

	EnemyRadarMirror RadarMirror;

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	Timer ShotTimer;
	Timer AfterSpawn;

	void FireShot();
	void AfterSpawnMovement();
};