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

	void SetLanderModel(Model model, Texture2D texture);
	void SetMutantModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	void SetLanderRadarModel(Model model, Texture2D texture);
	void SetPersonModel(Model model, Texture2D texture);
	void SetPersonRadar(Model model, Texture2D texture);
	void SetMutantRadarModel(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

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
	Texture2D LanderTexture;
	Texture2D MutantTexture;
	Texture2D ShotTexture;
	Texture2D PersonTexture;
	Texture2D LanderRadarTexture;
	Texture2D PersonRadarTexture;
	Texture2D MutantRadarTexture;

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;

	void SpawnLanders(int count);
	void SpawnMutant(Lander* lander);
	void SpawnPoeple(int count);
};