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

	void SetModel(Model model);
	void SetShotModel(Model model);
	void SetRadar(Model model);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position, Vector3 velocity);

private:
	EnemyRadarMirror RadarMirror;

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	Timer* ShotTimer = new Timer();
	Timer* AfterSpawn = new Timer();

	void FireShot();
	void AfterSpawnMovement();
};