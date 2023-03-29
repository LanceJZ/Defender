#pragma once
#include "Bomber.h"
#include "SharedData.h"
#include "ExplosionControl.h"
#include "ScoreKeeper.h"

class BomberControl : Common
{
public:
	std::vector<Bomber*> Bombers;

	BomberControl();
	virtual ~BomberControl();

	bool Initialize();
	void SetBomber(Model model);
	void SetBomb(Model model);
	void SetBomberRadar(Model model);
	void SetPlayer(Player* player);
	void SetData(SharedData* data);
	void SetExplosion(ExplosionControl* explosion);
	void SetSounds(Sound explosion);
	void SetScore(ScoreKeeper* score);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void NewWave();
	void Reset();

private:
	Model BomberModel = { 0 };
	Model BombModel = { 0 };
	Model BomberRadarModel = { 0 };

	Sound ExplosionSound = { 0 };
	Sound ShotSound = { 0 };

	SharedData* Data;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	ExplosionControl* Explosion = nullptr;
	ScoreKeeper* Score = nullptr;

	void SpawnBombers(int amount);
};

