#include "LanderMutantControl.h"

LanderMutantControl::~LanderMutantControl()
{
}

void LanderMutantControl::SetLanderModel(Model model)
{
	LanderModel = model;
}

void LanderMutantControl::SetMutantModel(Model model)
{
	MutantModel = model;
}

void LanderMutantControl::SetShotModel(Model model)
{
	ShotModel = model;
}

void LanderMutantControl::SetLanderRadarModel(Model model)
{
	LanderRadar = model;
}

void LanderMutantControl::SetPersonModel(Model model)
{
	PersonModel = model;
}

void LanderMutantControl::SetPersonRadar(Model model)
{
	PersonRadar = model;
}

void LanderMutantControl::SetMutantRadarModel(Model model)
{
	MutantRadar = model;
}

void LanderMutantControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool LanderMutantControl::Initialize()
{

	return false;
}

bool LanderMutantControl::BeginRun(Camera* camera)
{
	TheCamera = camera;
	SpawnLanders(15);
	SpawnPoeple(10);

	for (auto lander : Landers)
	{
		lander->BeginRun(camera);
	}

	for (auto person : People)
	{
		person->BeginRun(camera);
	}

	return false;
}

void LanderMutantControl::Update(float deltaTime)
{
	for (auto lander : Landers)
	{
		lander->Update(deltaTime);

		if (lander->MutateLander)
		{
			lander->MutateLander = false;
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
			Landers[Landers.size() - 1]->TheModel= LanderModel;
			Landers[Landers.size() - 1]->SetRadarModel(LanderRadar);
			Landers[Landers.size() - 1]->SetShotModel(ShotModel);
			Landers[Landers.size() - 1]->SetPlayer(ThePlayer);
			Landers[Landers.size() - 1]->Spawn({x, y, 0});
		}
	}
}

void LanderMutantControl::SpawnMutant(Lander* lander)
{
	Mutants.push_back(new Mutant());
	{
		Mutants[Mutants.size() - 1]->Initialize();
		Mutants[Mutants.size() - 1]->TheModel = MutantModel;
		Mutants[Mutants.size() - 1]->SetRadarModel(MutantRadar);
		Mutants[Mutants.size() - 1]->SetShotModel(ShotModel);
		Mutants[Mutants.size() - 1]->SetPlayer(ThePlayer);
		Mutants[Mutants.size() - 1]->BeginRun(TheCamera);
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
			People[People.size() - 1]->TheModel = PersonModel;
			People[People.size() - 1]->SetRadar(PersonRadar);
			People[People.size() - 1]->SetPlayer(ThePlayer);
			People[People.size() - 1]->Spawn({ x, y, 0 });
		}
	}

	for (auto lander : Landers)
	{
		lander->People = People;
	}
}