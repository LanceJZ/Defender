#pragma once
#include "Common.h"
#include "Player.h"
#include "Bomber.h"

class BomberControl : Common
{
public:
	vector<Bomber*> Bombers;

	BomberControl();
	virtual ~BomberControl();

	void SetBomber(Model model, Texture2D texture);
	void SetBomb(Model model, Texture2D texture);
	void SetBomberRadar(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model BomberModel = { 0 };
	Model BombModel = { 0 };
	Model BomberRadarModel = { 0 };
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;

	void SpawnBombers(int amount);
};

