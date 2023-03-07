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

void LanderMutantControl::SetRadarModel(Model model, Texture2D texture)
{
	LanderRadar = model;
	LanderRadarTexture = texture;
}

void LanderMutantControl::SetPersonModel(Model model, Texture2D texture)
{
	PersonModel = model;
	PersonTexture = texture;
}

void LanderMutantControl::SetPersonRadar(Model model, Texture2D texture)
{
	PersonRadar = model;
	PersonRadarTexture = texture;
}

void LanderMutantControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void LanderMutantControl::SetCamera(Camera* camera)
{
	TheCamera = camera;
}

bool LanderMutantControl::Initialize()
{

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

	//SpawnMutant(Landers[GetRandomValue(0, Landers.size() - 1)]);

	return false;
}

void LanderMutantControl::Update(float deltaTime)
{
	for (auto lander : Landers)
	{
		lander->Update(deltaTime);

		if (lander->MutateLander)
		{
			SpawnMutant(lander);
		}
	}

	for (auto mutant : Mutants)
	{
		mutant->Update(deltaTime);
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

	for (auto mutant : Mutants)
	{
		mutant->Draw();
	}

	for (auto person : People)
	{
		person->Draw();
	}
}

void LanderMutantControl::SpawnLanders(int count)
{
	//(-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i); The land size i = 0 to 6, so 7 times Screen Width.

	for (int i = 0; i < count; i++)
	{
		float x = GetRandomFloat((-GetScreenWidth() * 3.5f), (GetScreenWidth() * 3.5f));
		float y = GetScreenHeight() * 0.333f;

		Landers.push_back(new Lander());
		{
			Landers[Landers.size() - 1]->Initialize();
			Landers[Landers.size() - 1]->SetModel(LanderModel, LanderTexture);
			Landers[Landers.size() - 1]->SetShotModel(ShotModel, ShotTexture);
			Landers[Landers.size() - 1]->SetRadarModel(LanderModel, LanderRadarTexture);
			Landers[Landers.size() - 1]->SetPlayer(ThePlayer);
			Landers[Landers.size() - 1]->SetCamera(TheCamera);
			Landers[Landers.size() - 1]->Spawn({x, y, 0});
		}
	}
}

void LanderMutantControl::SpawnMutant(Lander* lander)
{
	Mutants.push_back(new Mutant());
	{
		Mutants[Mutants.size() - 1]->Initialize();
		Mutants[Mutants.size() - 1]->SetModel(MutantModel, MutantTexture);
		Mutants[Mutants.size() - 1]->SetShotModel(ShotModel, ShotTexture);
		Mutants[Mutants.size() - 1]->SetCamera(TheCamera);
		Mutants[Mutants.size() - 1]->SetPlayer(ThePlayer);
		Mutants[Mutants.size() - 1]->Spawn(lander->Position);
	}
}

void LanderMutantControl::SpawnPoeple(int count)
{
	for (int i = 0; i < count; i++)
	{
		float x = GetRandomFloat((-GetScreenWidth() * 3.5f), (GetScreenWidth() * 3.5f));
		float y = -(GetScreenHeight() / 2.10f);

		People.push_back(new Person());
		{
			People[People.size() - 1]->Initialize();
			People[People.size() - 1]->SetModel(PersonModel, PersonTexture);
			People[People.size() - 1]->SetRadar(PersonRadar, PersonRadarTexture);
			People[People.size() - 1]->SetPlayer(ThePlayer);
			People[People.size() - 1]->SetCamera(TheCamera);
			People[People.size() - 1]->Spawn({ x, y, 0 });
		}
	}

	for (auto lander : Landers)
	{
		lander->People = People;
	}
}