#pragma once
#include "Common.h"
#include "Player.h"
#include "Baiter.h"
#include "Timer.h"
#include "SharedData.h"
#include "ExplosionControl.h"
#include "ScoreKeeper.h"

class BaiterControl : Common
{
public:
	BaiterControl();
	virtual ~BaiterControl();

	bool IsOn = false;
	bool IsDown = false;

	std::vector<Baiter*> Baiters;

	bool Initialize();

	void SetPlayer(Player* player);
	void SetModels(Model baiter, Model shot);
	void SetRadarModel(Model radar);
	void SetSounds(Sound baiter, Sound shot, Sound explode);
	void SetExplosion(ExplosionControl* explosion);
	void SetData(SharedData* data);
	void SetScore(ScoreKeeper* score);

	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Activate();
	void Deactivate();
	void Smartbomb(float xMin, float xMax);
	void NewWave();
	void IsDownTime();

private:
	Model BaiterModel = { 0 };
	Model ShotModel = { 0 };
	Model RadarModel = { 0 };
	Sound BaiterSound = { 0 };
	Sound ShotSound = { 0 };
	Sound ExplosionSound = { 0 };
	Sound BaiterShotSound = { 0 };

	Timer SpawnTimer = {};
	Timer WaveTimer = {};
	Timer DownToTimer = {};
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;
	ExplosionControl* Explosion = nullptr;
	ScoreKeeper* Score = nullptr;
	SharedData* Data = nullptr;

	void Spawn();
};