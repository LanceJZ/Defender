#pragma once
#include "Bomber.h"
#include "SharedData.h"

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
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model BomberModel = { 0 };
	Model BombModel = { 0 };
	Model BomberRadarModel = { 0 };
	SharedData* Data;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;

	void SpawnBombers(int amount);
};

