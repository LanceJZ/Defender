#pragma once
#include "Model3D.h"
#include "Timer.h"
#include "EnemyMirror.h"

class Bomb : public Model3D
{
public:
	Bomb();
	virtual ~Bomb();

	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);

private:
	Timer LifeTimer;
	EnemyMirror Mirror;
};