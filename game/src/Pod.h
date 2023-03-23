#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Swarmer.h"
#include "EnemyRadarMirror.h"

class Pod : public Model3D
{
public:
	Pod();
	virtual ~Pod();

	vector<Swarmer*> Swarmers;

	bool Initialize();
	void SetShotModel(Model model);
	void SetSwarmerModel(Model model);
	void SetSwarmerRadarModel(Model model);
	void SetRadar(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float xVol);

private:
	EnemyRadarMirror RadarMirror;
	Model SwarmerModel = { 0 };
	Model SwarmerRadarModel = { 0 };
	Model ShotModel = { 0 };
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;

	void SpawnSwarmers(int count);
};