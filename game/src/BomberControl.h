#pragma once
#include "Bomber.h"
#include "SharedData.h"
#include "ExplosionControl.h"

class BomberControl : Common
{
public:
	vector<Bomber*> Bombers;

	BomberControl();
	virtual ~BomberControl();

	bool Initialize();
	void SetBomber(Model model);
	void SetBomb(Model model);
	void SetBomberRadar(Model model);
	void SetPlayer(Player* player);
	void SetData(SharedData* data);
	void SetExplosion(ExplosionControl* explosion);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void NewWave();
	void Reset();

private:
	Model BomberModel = { 0 };
	Model BombModel = { 0 };
	Model BomberRadarModel = { 0 };
	SharedData* Data;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	ExplosionControl* Explosion = nullptr;

	void SpawnBombers(int amount);
};

