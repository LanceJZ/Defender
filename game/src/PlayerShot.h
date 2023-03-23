#pragma once
#include "Model3D.h"
#include "Timer.h"
#include "EnemyMirror.h"

class PlayerShot : public Model3D
{
public:
	PlayerShot();
	virtual ~PlayerShot();

	bool Initialize();
	void SetTailModel(Model model);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, Vector3 velocity, bool reverse);
	void Reset();

private:
	Timer LifeTimer;
	Model3D Tail;
	EnemyMirror Mirror;
};

