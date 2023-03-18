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


	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position, Vector3 velocity, bool reverse);
	void Reset();

private:
	Timer* LifeTimer = new Timer();
	Model3D* Tail = new Model3D();
	EnemyMirror Mirror;
};

