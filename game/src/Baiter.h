#pragma once
#include "Enemy.h"

class Baiter : public Enemy
{
public:
	Baiter();
	virtual ~Baiter();

	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn();
	void Reset();

private:
	float XVelocity = 0;
	float YVelocity = 0;

	Timer AfterSpawnTimer;
	Timer SpeedChangeTimer;

	void AfterSpawnMovement();
	void ChangeSpeed();
	void FireShot();
	bool CheckCollision();
	void Destroy();

};