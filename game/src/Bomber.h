#pragma once
#include "Enemy.h"
#include "EnemyShot.h"
#include "Timer.h"
#include "ExplosionControl.h"

class Bomber : public Enemy
{
public:
	std::vector<EnemyShot*> Bombs;

	Bomber();
	virtual ~Bomber();

	bool Initialize();
	void SetBomb(Model model);
	void SetExplosion(ExplosionControl* explosion);

	bool BeginRun(Camera *camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float x);
	void Reset();


private:
	Model BombModel = { 0 };
	Timer DropBombTimer;
	ExplosionControl* Explosion = nullptr;

	void DropABomb();
	bool CheckCollision();
	void Destroy();
};