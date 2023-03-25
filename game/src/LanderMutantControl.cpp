#include "LanderMutantControl.h"

LanderMutantControl::LanderMutantControl()
{
}

LanderMutantControl::~LanderMutantControl()
{
	Data = nullptr;
	Landers.clear();
	Mutants.clear();
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

void LanderMutantControl::SetPlayer(Player *player)
{
	ThePlayer = player;
}

void LanderMutantControl::SetData(SharedData *data)
{
	Data = data;
}

void LanderMutantControl::SetSounds(Sound shot, Sound explode, Sound person)
{
	ShotSound = shot;
	ExplodeSound = explode;
	PersonGrabbedSound = person;
}

bool LanderMutantControl::BeginRun(Camera *camera)
{
	TheCamera = camera;

	for (int personNumber = 0; personNumber < 10; personNumber++)
	{
		People[personNumber].Initialize();
		People[personNumber].SetModel(PersonModel, 5.0f);
		People[personNumber].SetRadar(PersonRadar);
		People[personNumber].SetPlayer(ThePlayer);
		People[personNumber].BeginRun(TheCamera);
	}

	SpawnPoeple(10);
	StartLanderWave();
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

	for (auto &person : People)
	{
		person.Update(deltaTime);

		if (person.CountChanged)
		{
			person.CountChanged = false;
			CountPeopleChange();
		}
	}

	if (SpawnTimer.Elapsed())
	{
		SpawnTimer.Reset();

		if (NumberSpawned < TotalSpawn)
		{
			SpawnMoreLanders();
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

	for (auto &person : People)
	{
		person.Draw();
	}
}

void LanderMutantControl::SpawnMoreLanders()
{
	int spawn = 5;

	if (NumberSpawned + spawn > TotalSpawn)
	{
		spawn = TotalSpawn - NumberSpawned;
	}

	SpawnLanders(spawn);
	SpawnTimer.Reset(SpawnTimerAmount);

	if (LandersTurnedToMutants)
	{
		for (auto lander : Landers)
		{
			if (lander->Enabled)
			{
				SpawnMutant(lander);
			}
		}

		SpawnTimer.Reset(0.5f);
	}
}

void LanderMutantControl::SpawnLanders(int count)
{
	//The land size i = 0 to 6, so 7 times Screen Width and shifted over half a screen width for center.
	float screenMulti = 3.5f;

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
			landerNumber = (int)Landers.size();
			Landers.push_back(new Lander());
			{
				Landers[landerNumber]->Initialize();
				Landers[landerNumber]->SetModel(LanderModel, 14.0f);
				Landers[landerNumber]->SetRadarModel(LanderRadar, 3.0f);
				Landers[landerNumber]->SetShotModel(ShotModel);
				Landers[landerNumber]->SetPlayer(ThePlayer);
				Landers[landerNumber]->SetSounds(ShotSound, ExplodeSound);
				Landers[landerNumber]->SetPersonSound(PersonGrabbedSound);
				Landers[landerNumber]->BeginRun(TheCamera);
			}
		}

		float x = GetRandomFloat((-GetScreenWidth() * screenMulti), (GetScreenWidth() * screenMulti));
		float y = GetScreenHeight() * 0.333f;
		Landers[landerNumber]->Spawn({x, y, 0});

		for (int i = 0; i < 10; i++)
		{
			Landers[landerNumber]->People[i] = &People[i];
		}
	}

	NumberSpawned += count;
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
		mutantNumber = (int)Mutants.size();
		Mutants.push_back(new Mutant());
		{
			Mutants[mutantNumber]->Initialize();
			Mutants[mutantNumber]->SetModel(MutantModel, 14.0f);
			Mutants[mutantNumber]->SetRadarModel(MutantRadar, 3.0f);
			Mutants[mutantNumber]->SetShotModel(ShotModel);
			Mutants[mutantNumber]->SetPlayer(ThePlayer);
			Mutants[mutantNumber]->SetSounds(ShotSound, ExplodeSound);
			Mutants[mutantNumber]->BeginRun(TheCamera);
		}
	}

	Mutants[mutantNumber]->Spawn(lander->Position);
	lander->Enabled = false;
}

void LanderMutantControl::SpawnPoeple(int count)
{
	for (int i = 0; i < count; i++)
	{
		float x = GetRandomFloat((-GetScreenWidth() * 3.5f), (GetScreenWidth() * 3.5f));
		float y = -(GetScreenHeight() / 2.10f);
		People[i].Spawn({ x, y, 0 });
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

	if (NumberSpawned < TotalSpawn)
	{
		SpawnMoreLanders();
		return;
	}

	Data->LandersMutantsBeGone = true;
}

void LanderMutantControl::CountPeopleChange()
{
	for (auto &person : People)
	{
		if (person.Enabled)
		{
			return;
		}
	}

	Data->PeopleBeGone = true;
}

void LanderMutantControl::TheyAllDied()
{
	for (auto lander : Landers)
	{
		if (lander->Enabled)
		{
			SpawnMutant(lander);
		}
	}

	LandersTurnedToMutants = true;
}

void LanderMutantControl::StartLanderWave()
{
	for (auto &person : People)
	{
		person.Y(-(GetScreenHeight() / 2.10f));
	}

	NumberSpawned = 0;
	SpawnMoreLanders();

	//SpawnLanders(5);

	//SpawnTimer.Reset(SpawnTimerAmount);
}

void LanderMutantControl::NewLevelWave()
{
	for (auto lander : Landers)
	{
		for (auto &shot : lander->Shots)
		{
			shot.Enabled = false;
		}
	}

	for (auto mutant : Mutants)
	{
		for (auto &shot : mutant->Shots)
		{
			shot.Enabled = false;
		}
	}

	if (TotalSpawn < 30)
		TotalSpawn += NumberSpawned;

	int numberOfPeopleAlive = 0;

	for (auto &person : People)
	{
		if (person.Enabled)
		{
			numberOfPeopleAlive++;
		}

		person.Destroy();
	}

	LandersTurnedToMutants = false;
	SpawnPoeple(numberOfPeopleAlive);
	StartLanderWave();
}

void LanderMutantControl::PlayerHitReset()
{
	int peopleAlive = 0;
	int landersAlive = 0;
	int mutantsAlive = 0;

	for (auto lander : Landers)
	{
		if (lander->Enabled)
		{
			landersAlive++;
			lander->Reset();
		}

		for (auto &shot : lander->Shots)
		{
			shot.Enabled = false;
		}
	}

	for (auto mutant : Mutants)
	{
		for (auto &shot : mutant->Shots)
		{
			shot.Enabled = false;
		}
	}

	for (auto &person : People)
	{
		person.Reset();
	}

	NumberSpawned = NumberSpawned - landersAlive;

	SpawnMoreLanders();
}