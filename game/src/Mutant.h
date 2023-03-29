#pragma once
#include "Enemy.h"

class Mutant : public Enemy
{
public:
	Mutant();
	virtual ~Mutant();

	bool Initialize();
	bool BeginRun(Camera *camera);
	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);

private:
	bool GotNearPlayer = false;
	bool BackToToporBottom = false;
	float Speed = 100;

	Timer ChangeSpeedTimer;

	void FireShot();
	void ChasePlayer();
	bool CheckCollision();
	void Destroy();
};