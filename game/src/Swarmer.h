#pragma once
#include "raylib.h"
#include "Enemy.h"
#include "Timer.h"
#include "ExplosionControl.h"

class Swarmer : public Enemy
{
public:
	Swarmer();
	virtual ~Swarmer();

	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, Vector3 velocity);
	void Reset();

private:
	float XVolocity = 0;
	float YVolocity = 0;

	Timer AfterSpawnTimer;

	void FireShot();
	void AfterSpawnMovement();
	bool CheckCollision();
	void Destroy();
};