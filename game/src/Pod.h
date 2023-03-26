#pragma once
#include "raylib.h"
#include "SharedData.h"
#include "Enemy.h"
#include "Swarmer.h"
#include "ExplosionControl.h"

class Pod : public Enemy
{
public:
	Pod();
	virtual ~Pod();

	vector<Swarmer*> Swarmers;

	bool Initialize();
	void SetShotModel(Model model);
	void SetSwarmerModel(Model model);
	void SetSwarmerRadarModel(Model model);
	void SetData(SharedData* data);
	void SetExplosion(ExplosionControl* explosion);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float xVol);
	void Reset();

private:
	Model SwarmerModel = { 0 };
	Model SwarmerRadarModel = { 0 };
	Model ShotModel = { 0 };

	SharedData* Data = nullptr;
	ExplosionControl* Explosion = nullptr;

	void SpawnSwarmers(int count);
	bool CheckCollision();
	void Destroy();
};