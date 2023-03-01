#pragma once
#include "raylib.h"
#include "Lander.h"
#include "Person.h"
#include "Common.h"
#include "Player.h"

class LanderMutantControl : Common
{
public:
	virtual ~LanderMutantControl();

	vector<Lander*> Landers;
	vector<Person*> People; //The Person Man.

	void SetLanderModel(Model model, Texture2D texture);
	void SetMutantModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	void SetPersonModel(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model LanderModel;
	Model MutantModel;
	Model ShotModel;
	Model PersonModel;
	Texture2D LanderTexture;
	Texture2D MutantTexture;
	Texture2D ShotTexture;
	Texture2D PersonTexture;

	Player* ThePlayer;

	void SpawnLanders(int count);
	void SpawnPoeple(int count);
};