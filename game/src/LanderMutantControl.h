#pragma once
#include "raylib.h"
#include "Lander.h"

class LanderMutantControl
{
public:
	LanderMutantControl();
	virtual ~LanderMutantControl();

	vector<Lander*> Landers;

	void SetLanderModel(Model model, Texture2D texture);
	void SetMutantModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model LanderModel;
	Model MutantModel;
	Model ShotModel;
	Texture2D LanderTexture;
	Texture2D MutantTexture;
	Texture2D ShotTexture;

	void SpawnLander(int count);
};