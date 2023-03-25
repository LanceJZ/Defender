#pragma once
#include "Model3D.h"
#include "Player.h"
#include "EnemyRadarMirror.h"

class Person : public Model3D
{
public:
	enum PersonState
	{
		OnGround,
		GoingDown,
		CaughtByPlayer,
		TargetedByLander
	};

	PersonState State = OnGround;
	bool CountChanged = false;

	Person();
	virtual ~Person();

	bool Initialize();
	void SetRadar(Model &model);
	void SetPlayer(Player *player);
	bool BeginRun(Camera *camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void Dropped();
	void Destroy();
	void Reset();

private:
	float DroppedY = 0;
	EnemyRadarMirror RadarMirror;

	Player *ThePlayer = nullptr;

	void Falling();
	void GoingForARide();
	void CheckCollision();
};