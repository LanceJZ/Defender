#include "LanderMutantControl.h"

LanderMutantControl::~LanderMutantControl()
{
}

bool LanderMutantControl::Initialize()
{
	Common::Initialize();

	return false;
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

void LanderMutantControl::SetData(SharedData* data)
{
	Data = data;
}

bool LanderMutantControl::BeginRun(Camera* camera)
{
	TheCamera = camera;
	SpawnLanders(5);
	SpawnPoeple(10);
	SpawnTimer.Set(SpawnTimerAmount);

	return false;
}

void LanderMutantControl::Update(float deltaTime)
{
	SpawnTimer.Update(deltaTime);

	for (auto lander : Landers)
	{
		lander->Update(deltaTime);

		if (lander->MutateLander)
		{
			lander->MutateLander = false;
			SpawnMutant(lander);
		}

		if (lander->CountChange)
		{
			lander->CountChange = false;
			CountChange();
		}
	}

	for (auto mutant : Mutants)
	{
		mutant->Update(deltaTime);

		if (mutant->CountChange)
		{
			mutant->CountChange = false;
			CountChange();
		}
	}

	for (auto person : People)
	{
		person->Update(deltaTime);

		if (person->CountChanged)
		{
			person->CountChanged = false;
			CountPeopleChange();
		}
	}

	if (SpawnTimer.Elapsed())
	{
		SpawnTimer.Reset();

		if (NumberSpawned < TotalSpawn)
		{
			SpawnLanders(5);
			NumberSpawned += 5;
		}
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
	//The land size i = 0 to 6, so 7 times Screen Width and shifted over half a screen width.
	for (int i = 0; i < count; i++)
	{
		bool spawnNew = true;
		int landerNumber = 0;

		for (auto lander : Landers)
		{
			if (!lander->Enabled)
			{
				spawnNew = false;
				break;
			}

			landerNumber++;
		}


		if (spawnNew)
		{
			landerNumber = Landers.size();
			Landers.push_back(new Lander());
			{
				Landers[landerNumber]->Initialize();
				Landers[landerNumber]->SetModel(LanderModel);
				Landers[landerNumber]->SetRadarModel(LanderRadar);
				Landers[landerNumber]->SetShotModel(ShotModel);
				Landers[landerNumber]->SetPlayer(ThePlayer);
				Landers[landerNumber]->BeginRun(TheCamera);
			}
		}

		float x = GetRandomFloat((-GetScreenWidth() * 3.5f), (GetScreenWidth() * 3.5f));
		float y = GetScreenHeight() * 0.333f;
		Landers[landerNumber]->Spawn({x, y, 0});
	}

	Data->LandersMutantsBeGone = false;
}

void LanderMutantControl::SpawnMutant(Lander* lander)
{
	bool spawnNew = true;
	int mutantNumber = 0;

	for (auto mutant : Mutants)
	{
		if (!mutant->Enabled)
		{
			spawnNew = false;
			break;
		}

		mutantNumber++;
	}

	if (spawnNew)
	{
		mutantNumber = Mutants.size();
		Mutants.push_back(new Mutant());
		{
			Mutants[mutantNumber]->Initialize();
			Mutants[mutantNumber]->TheModel = MutantModel;
			Mutants[mutantNumber]->SetRadarModel(MutantRadar);
			Mutants[mutantNumber]->SetShotModel(ShotModel);
			Mutants[mutantNumber]->SetPlayer(ThePlayer);
			Mutants[mutantNumber]->BeginRun(TheCamera);
		}
	}

	Mutants[mutantNumber]->Spawn(lander->Position);
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
			People[People.size() - 1]->BeginRun(TheCamera);
			People[People.size() - 1]->Spawn({ x, y, 0 });
		}
	}

	for (auto lander : Landers)
	{
		lander->People = People;
	}
}

void LanderMutantControl::CountChange()
{
	for (auto lander : Landers)
	{
		if (lander->Enabled)
		{
			return;
		}
	}

	for (auto mutant : Mutants)
	{
		if (mutant->Enabled)
		{
			return;
		}
	}

	Data->LandersMutantsBeGone = true;
}

void LanderMutantControl::CountPeopleChange()
{
	for (auto person : People)
	{
		if (person->Enabled)
		{
			return;
		}
	}

	Data->PeopleBeGone = true;
}
