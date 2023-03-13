#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "EnemyMirror.h"
#include "EnemyRadar.h"
#include "Timer.h"

class Swarmer : public Model3D
{
public:
	Swarmer();
	virtual ~Swarmer();

	EnemyShot* Shots[4];

	void SetShotModel(Model model);
	void SetRadar(Model model);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	EnemyMirror Mirror;
	EnemyRadar Radar;

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	Timer* ShotTimer = new Timer();

	void FireShot();
};