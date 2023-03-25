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
	void SetPlayer(Player *player);
	void SetData(SharedData *data);
	void SetSounds(Sound shot, Sound explode, Sound person);
	bool BeginRun(Camera *camera);

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

	Model LanderModel = { 0 };
	Model MutantModel = { 0 };
	Model ShotModel = { 0 };
	Model PersonModel = { 0 };
	Model LanderRadar = { 0 };
	Model PersonRadar = { 0 };
	Model MutantRadar = { 0 };

	Sound ShotSound = { 0 };
	Sound ExplodeSound = { 0 };
	Sound PersonGrabbedSound = { 0 };
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