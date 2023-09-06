#pragma once
#include "Enemy.h"

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
	float XVelocity = 0;
	float YVelocity = 0;
	float DistanceX = 0;
	float DistanceY = 0;

	Timer AfterSpawnTimer;
	Timer DistanceTimer;

	void FireShot();
	void AfterSpawnMovement();
	bool CheckCollision();
	void Destroy();
};