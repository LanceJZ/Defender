#pragma once
#include "Lander.h"
#include "Mutant.h"
#include "Person.h"
#include "SharedData.h"

class LanderMutantControl : Common
{
public:
	LanderMutantControl();
	virtual ~LanderMutantControl();

	bool LandersTurnedToMutants = false;
	vector<Lander*> Landers;
	vector<Mutant*> Mutants;
	Person People[10]; //The Person Man.

	bool Initialize();
	void SetLanderModel(Model model);
	void SetMutantModel(Model model);
	void SetShotModel(Model model);
	void SetLanderRadarModel(Model model);
	void SetPersonModel(Model model);
	void SetPersonRadar(Model model);
	void SetMutantRadarModel(Model model);
	void SetPlayer(Player* player);
	void SetData(SharedData* data);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void StartLanderWave();
	void NewLevelWave();
	void PlayerHitReset();
	void TheyAllDied();

private:
	int TotalSpawn = 10;
	int NumberSpawned = 5;
	float SpawnTimerAmount = 30.0f;

	Model LanderModel;
	Model MutantModel;
	Model ShotModel;
	Model PersonModel;
	Model LanderRadar;
	Model PersonRadar;
	Model MutantRadar;

	Timer SpawnTimer;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	SharedData* Data = nullptr;

	void SpawnMoreLanders();
	void SpawnLanders(int count);
	void SpawnMutant(Lander* lander);
	void SpawnPoeple(int count);
	void CountChange();
	void CountPeopleChange();
};