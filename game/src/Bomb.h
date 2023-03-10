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

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	Timer* LifeTimer = new Timer();
	EnemyMirror Mirror;
};