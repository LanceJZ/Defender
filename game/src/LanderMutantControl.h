#pragma once
#include "Lander.h"
#include "Mutant.h"
#include "Person.h"
#include "SharedData.h"

class LanderMutantControl : Common
{
public:
	virtual ~LanderMutantControl();

	vector<Lander*> Landers;
	vector<Mutant*> Mutants;
	vector<Person*> People; //The Person Man.

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

	void NewLanderWave();
	void NewLevelWave();
	void PlayerHitReset();

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