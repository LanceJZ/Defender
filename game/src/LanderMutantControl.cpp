#include "LanderMutantControl.h"

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

void LanderMutantControl::SetPersonModel(Model model, Texture2D texture)
{
	PersonModel = model;
	PersonTexture = texture;
}

void LanderMutantControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool LanderMutantControl::Initialize()
{
	for (auto lander : Landers)
	{
		lander->Initialize();
	}

	for (auto person : People)
	{
		person->Initialize();
	}

	return false;
}

bool LanderMutantControl::BeginRun()
{
	SpawnLanders(15);
	SpawnPoeple(10);

	for (auto lander : Landers)
	{
		lander->BeginRun();
	}

	for (auto person : People)
	{
		person->BeginRun();
	}

	return false;
}

void LanderMutantControl::Update(float deltaTime)
{
	for (auto lander : Landers)
	{
		lander->Update(deltaTime);
	}

	for (auto person : People)
	{
		person->Update(deltaTime);
	}
}

void LanderMutantControl::Draw()
{
	for (auto lander : Landers)
	{
		lander->Draw();
	}

	for (auto person : People)
	{
		person->Draw();
	}
}

void LanderMutantControl::SpawnLanders(int count)
{
	//(-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i) land size i = 0 to 6;

	for (int i = 0; i < count; i++)
	{
		float x = GetRandomFloat((-GetScreenWidth() * 3.0f), (GetScreenWidth() * 3.0f));
		float y = GetScreenHeight() / 3.0f;

		Landers.push_back(new Lander());
		{
			Landers[Landers.size() - 1]->Initialize();
			Landers[Landers.size() - 1]->SetModel(LanderModel, LanderTexture);
			Landers[Landers.size() - 1]->SetShotModel(ShotModel, ShotTexture);
			Landers[Landers.size() - 1]->SetPlayer(ThePlayer);
			Landers[Landers.size() - 1]->Spawn({x, y, 0});
		}
	}
}

void LanderMutantControl::SpawnPoeple(int count)
{
	for (int i = 0; i < count; i++)
	{
		float x = GetRandomFloat((-GetScreenWidth() * 3), (GetScreenWidth() * 3));
		float y = -(GetScreenHeight() / 2.10f);

		People.push_back(new Person());
		{
			People[People.size() - 1]->Initialize();
			People[People.size() - 1]->SetModel(PersonModel, PersonTexture);
			People[People.size() - 1]->SetPlayer(ThePlayer);
			People[People.size() - 1]->Spawn({ x, y, 0 });
		}
	}
}