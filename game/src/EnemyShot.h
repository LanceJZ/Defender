#pragma once
#include "Model3D.h"
#include "EnemyMirror.h"
#include "Timer.h"
#include "Player.h"

class EnemyShot : public Model3D
{
public:
	virtual ~EnemyShot();

	bool Initialize();
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position, Vector3 velocity, float life);
	float GetShotAngle(Vector3 position);
	float AimedShot(Vector3 position);

private:
	Player* ThePlayer = nullptr;
	Timer LifeTimer;
	EnemyMirror Mirror;
};