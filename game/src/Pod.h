#pragma once
#include "Enemy.h"
#include "SharedData.h"
#include "Swarmer.h"

class Pod : public Enemy
{
public:
	Pod();
	virtual ~Pod();

	std::vector<Swarmer*> Swarmers;

	bool Initialize();
	void SetShotModel(Model model);
	void SetSwarmerModel(Model model);
	void SetSwarmerRadarModel(Model model);
	void SetSwarmerExplodeSound(Sound sound);
	void SetData(SharedData* data);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float xVol);
	void Reset();

private:
	Model SwarmerModel = { 0 };
	Model SwarmerRadarModel = { 0 };
	Model ShotModel = { 0 };
	Sound SwarmerExplodeSound = { 0 };

	SharedData* Data = nullptr;

	void SpawnSwarmers(int count);
	bool CheckCollision();
	void Destroy();
};