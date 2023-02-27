#include "LanderMutantControl.h"

LanderMutantControl::LanderMutantControl()
{

}

LanderMutantControl::~LanderMutantControl()
{
}

void LanderMutantControl::SetLanderModel(Model model, Texture2D texture)
{
	LanderModel = model;
	LanderTexture = texture;
}

void LanderMutantControl::SetMutantModel(Model model, Texture2D texture)
{
	MutantModel = model;
	MutantTexture = texture;
}

void LanderMutantControl::SetShotModel(Model model, Texture2D texture)
{
	ShotModel = model;
	ShotTexture = texture;
}

bool LanderMutantControl::Initialize()
{
	return false;
}

bool LanderMutantControl::BeginRun()
{
	SpawnLander(15);

	for (auto lander : Landers)
	{
		lander->BeginRun();
	}

	return false;
}

void LanderMutantControl::Update(float deltaTime)
{
	for (auto lander : Landers)
	{
		lander->Update(deltaTime);
	}
}

void LanderMutantControl::Draw()
{
	for (auto lander : Landers)
	{
		lander->Draw();
	}
}

void LanderMutantControl::SpawnLander(int count)
{
	//(-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i) land size i = 0 to 6;

	for (int i = 0; i < count; i++)
	{
		float x = GetRandomFloat((-GetScreenWidth() * 3), (GetScreenWidth() * 3));
		float y = GetScreenHeight() / 3;

		Landers.push_back(new Lander());
		{
			Landers[Landers.size() - 1]->Initialize();
			Landers[Landers.size() - 1]->LoadModel(LanderModel, LanderTexture);
			Landers[Landers.size() - 1]->SetShotModel(ShotModel, ShotTexture);
			Landers[Landers.size() - 1]->Spawn({x, y, 0});
		}
	}
}
