#pragma once
#include "Common.h"
#include "Lander.h"
#include "Mutant.h"
#include "Person.h"
#include "Player.h"

class LanderMutantControl : Common
{
public:
	virtual ~LanderMutantControl();

	vector<Lander*> Landers;
	vector<Mutant*> Mutants;
	vector<Person*> People; //The Person Man.

	void SetLanderModel(Model model);
	void SetMutantModel(Model model);
	void SetShotModel(Model model);
	void SetLanderRadarModel(Model model);
	void SetPersonModel(Model model);
	void SetPersonRadar(Model model);
	void SetMutantRadarModel(Model model);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model LanderModel;
	Model MutantModel;
	Model ShotModel;
	Model PersonModel;
	Model LanderRadar;
	Model PersonRadar;
	Model MutantRadar;

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;

	void SpawnLanders(int count);
	void SpawnMutant(Lander* lander);
	void SpawnPoeple(int count);
};