#pragma once
#include "Enemy.h"
#include "Bomb.h"
#include "Timer.h"

class Bomber : public Enemy
{
public:
	vector<Bomb*> Bombs;

	Bomber();
	virtual ~Bomber();

	bool Initialize();
	void SetBomb(Model model);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float x);

private:
	Model BombModel = { 0 };
	Timer DropBombTimer;

	void DropABomb();
};