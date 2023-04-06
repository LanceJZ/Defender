#pragma once
#include "Pod.h"
#include "SharedData.h"
#include "ExplosionControl.h"
#include "ScoreKeeper.h"

class PodSwarmerControl : Common
{
public:
	std::vector<Pod*> Pods;
	std::vector<Swarmer*> Swarmers;

	PodSwarmerControl();
	virtual ~PodSwarmerControl();

	bool Initialize();
	void SetPodModel(Model model);
	void SetSwarmerModel(Model model);
	void SetShotModel(Model model);
	void SetPodRadarModel(Model model);
	void SetSwarmerRadarModel(Model model);
	void SetSounds(Sound explodeSound, Sound swarmerExplode, Sound shotSound);
	void SetPlayer(Player* player);
	void SetData(SharedData* data);
	void SetExplosion(ExplosionControl* explosion);
	void SetScore(ScoreKeeper* score);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void NewWave();
	void Reset();
	void Smartbomb(float xMin, float xMax);

private:
	Model PodModel = { 0 };
	Model SwarmerModel = { 0 };
	Model ShotModel = { 0 };
	Model PodRadarModel = { 0 };
	Model SwarmerRadarModel = { 0 };
	Sound SwarmerShotSound = { 0 };
	Sound PodExplodeSound = { 0 };
	Sound SwarmerExplodeSound = { 0 };

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	SharedData* Data = nullptr;
	ExplosionControl* Explosion = nullptr;
	ScoreKeeper* Score = nullptr;

	void SpawnPods(int count);
	void SpawnSwarmers(Vector3 position, int count);
};

