#pragma once
#include "Common.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "Player.h"
#include "EnemyRadarMirror.h"

class Enemy : public Model3D
{
public:
	Enemy();
	virtual ~Enemy();

	bool CountChange = false;
	EnemyShot Shots[4];

	bool Initialize();
	void SetRadarModel(Model model, float scale);
	void SetShotModel(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void Spawn(Vector3 position);
	virtual void Reset();

protected:
	Timer ShotTimer;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;

	virtual bool CheckCollision();
	virtual void Destroy();
	virtual void FireShot();

private:
	EnemyRadarMirror RadarMirror;
};

