#include "LanderMutantControl.h"

LanderMutantControl::LanderMutantControl()
{
}

LanderMutantControl::~LanderMutantControl()
{
	Data = nullptr;

	for (int i = 0; i < Landers.size(); i++)
	{
		delete Landers[i];
	}

	Landers.clear();

	for (int i = 0; i < Mutants.size(); i++)
	{
		delete Mutants[i];
	}

	Mutants.clear();

	//UnloadModel(ShotModel);
	//UnloadModel(LanderModel);
	//UnloadModel(MutantModel);
	//UnloadModel(PersonModel);
	//UnloadModel(LanderRadar);
	//UnloadModel(MutantRadar);
	//UnloadModel(PersonRadar);

	//UnloadSound(ExplodeSound);
	//UnloadSound(ShotSound);
	//UnloadSound(LanderMutateSound);
	//UnloadSound(LanderSpawnSound);
	//UnloadSound(MutantShotSound);
	//UnloadSound(PersonCaughtSound);
	//UnloadSound(PersonDroppedSound);
	//UnloadSound(PersonGrabbedSound);
	//UnloadSound(PersonLeftSound);
	//UnloadSound(PersonSplatSound);

	ThePlayer = nullptr;
	TheCamera = nullptr;
	Data = nullptr;
	Explosion = nullptr;
	Score = nullptr;
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

void LanderMutantControl::SetSounds(Sound shot, Sound explode,
	Sound mutant, Sound landerMutate, Sound landerSpawn)
{
	ShotSound = shot;
	MutantShotSound = mutant;
	LanderMutateSound = landerMutate;
	ExplodeSound = explode;
	LanderSpawnSound = landerSpawn;
}

void LanderMutantControl::SetPersonSounds(Sound grabbed, Sound dropped, Sound caught,
	Sound left, Sound splat)
{
	PersonGrabbedSound = grabbed;
	PersonDroppedSound = dropped;
	PersonCaughtSound = caught;
	PersonLeftSound = left;
	PersonSplatSound = splat;
}

void LanderMutantControl::SetExplosion(ExplosionControl* explosion)
{
	Explosion = explosion;
}

void LanderMutantControl::SetScore(ScoreKeeper* score)
{
	Score = score;
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
		People[personNumber].SetExplosion(Explosion);
		People[personNumber].SetSounds(PersonCaughtSound, PersonLeftSound,
			PersonSplatSound);
		People[personNumber].SetScore(Score);
		People[personNumber].BeginRun(TheCamera);
	}

	SpawnPoeple(10);
	return false;
}

void LanderMutantControl::SpawnPoeple(int count)
{
	for (int i = 0; i < count; i++)
	{
		float x = GetRandomFloat((-GetScreenWidth() * 3.49f),
			(GetScreenWidth() * 3.49f));
		float y = -(GetScreenHeight() / 2.10f);
		People[i].Spawn({ x, y, 0 });
	}
}

void LanderMutantControl::Update(float deltaTime)
{
	SpawnTimer.Update(deltaTime);

	for (const auto& lander : Landers)
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

	for (const auto& mutant : Mutants)
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
	for (const auto& lander : Landers)
	{
		lander->Draw();
	}

	for (const auto& mutant : Mutants)
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
	PlaySound(LanderSpawnSound);
	int spawn = 5;

	if (NumberSpawned + spawn > TotalSpawn)
	{
		spawn = TotalSpawn - NumberSpawned;
	}

	SpawnLanders(spawn);
	SpawnTimer.Reset(SpawnTimerAmount);

	if (LandersTurnedToMutants)
	{
		for (const auto& lander : Landers)
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
		int landerSpawnNumber = (int)Landers.size();

		for (const auto& lander : Landers)
		{
			if (!lander->Enabled)
			{
				spawnNew = false;
				landerSpawnNumber = landerNumber;
				break;
			}

			landerNumber++;
		}


		if (spawnNew)
		{
			Landers.push_back(DBG_NEW Lander());
			{
				Landers[landerSpawnNumber]->Initialize();
				Landers[landerSpawnNumber]->SetModel(LanderModel, 14.0f);
				Landers[landerSpawnNumber]->SetRadarModel(LanderRadar, 3.0f);
				Landers[landerSpawnNumber]->SetShotModel(ShotModel);
				Landers[landerSpawnNumber]->SetPlayer(ThePlayer);
				Landers[landerSpawnNumber]->SetExplosion(Explosion);
				Landers[landerSpawnNumber]->SetSounds(ShotSound, ExplodeSound);
				Landers[landerSpawnNumber]->SetPersonSound(PersonGrabbedSound,
					PersonDroppedSound, LanderMutateSound);
				Landers[landerSpawnNumber]->SetScore(Score, 150);
				Landers[landerSpawnNumber]->BeginRun(TheCamera);
			}
		}

		float x = GetRandomFloat((-GetScreenWidth() * screenMulti),
			(GetScreenWidth() * screenMulti));
		float y = GetScreenHeight() * 0.333f;
		Landers[landerSpawnNumber]->Spawn({x, y, 0});

		for (int i = 0; i < 10; i++)
		{
			Landers[landerSpawnNumber]->People[i] = &People[i];
		}
	}

	NumberSpawned += count;
	Data->LandersMutantsBeGone = false;
}

void LanderMutantControl::SpawnMutant(Lander* lander)
{
	bool spawnNew = true;
	int mutantNumber = 0;
	int mutantSpawnNumber = (int)Mutants.size();

	for (const auto& mutant : Mutants)
	{
		if (!mutant->Enabled)
		{
			spawnNew = false;
			mutantSpawnNumber = mutantNumber;
			break;
		}

		mutantNumber++;
	}

	if (spawnNew)
	{
		Mutants.push_back(DBG_NEW Mutant());
		{
			Mutants[mutantSpawnNumber]->Initialize();
			Mutants[mutantSpawnNumber]->SetModel(MutantModel, 14.0f);
			Mutants[mutantSpawnNumber]->SetRadarModel(MutantRadar, 3.0f);
			Mutants[mutantSpawnNumber]->SetShotModel(ShotModel);
			Mutants[mutantSpawnNumber]->SetPlayer(ThePlayer);
			Mutants[mutantSpawnNumber]->SetExplosion(Explosion);
			Mutants[mutantSpawnNumber]->SetSounds(MutantShotSound, ExplodeSound);
			Mutants[mutantSpawnNumber]->SetScore(Score, 150);
			Mutants[mutantSpawnNumber]->BeginRun(TheCamera);
		}
	}

	Mutants[mutantSpawnNumber]->Spawn(lander->Position);
	lander->Reset();
}

void LanderMutantControl::CountChange()
{
	for (const auto& lander : Landers)
	{
		if (lander->Enabled)
		{
			return;
		}
	}

	for (const auto& mutant : Mutants)
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
	NumberMutants = 0;
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
	for (const auto& lander : Landers)
	{
		if (lander->Enabled)
		{
			SpawnMutant(lander);
		}
	}

	LandersTurnedToMutants = true;
}

void LanderMutantControl::Smartbomb(float xMin, float xMax)
{
	for (const auto& lander : Landers)
	{
		if (lander->Enabled)
		{
			if (lander->X() > xMin && lander->X() < xMax)
			{
				if (lander->Enabled)
				{
					Score->AddToScore(lander->ScoreAmount);
					lander->Hit();
					lander->Reset();
				}
			}
		}
	}

	for (const auto& mutant : Mutants)
	{
		if (mutant->Enabled)
		{
			if (mutant->X() > xMin && mutant->X() < xMax)
			{
				if (mutant->Enabled)
				{
					Score->AddToScore(mutant->ScoreAmount);
					mutant->Hit();
					mutant->Reset();
				}
			}
		}
	}
}

void LanderMutantControl::StartLanderWave()
{
	for (auto &person : People)
	{
		person.Y(-(GetScreenHeight() / 2.10f));
	}

	SpawnMoreLanders();
}

void LanderMutantControl::StartWave()
{
	for (const auto& lander : Landers)
	{
		for (auto &shot : lander->Shots)
		{
			shot.Enabled = false;
		}

		lander->Reset();
	}

	for (const auto& mutant : Mutants)
	{
		for (auto &shot : mutant->Shots)
		{
			shot.Enabled = false;
		}

		mutant->Reset();
	}

	if (NumberofPeopleAlive > 0)
	{
		LandersTurnedToMutants = false;

		int peopleAlive = 0;

		for (auto &person : People)
		{
			if (person.Enabled)
			{
				peopleAlive++;
			}
		}

		if (peopleAlive < NumberofPeopleAlive)
		{
			SpawnPoeple(NumberofPeopleAlive - peopleAlive);

		}
	}

	StartLanderWave();

	for (int i = 0; i < NumberMutants; i++)
	{
		Mutants[i]->Spawn({ GetScreenWidth() * 3.5f,
			GetScreenHeight() * 0.5f, 0});
	}
}

void LanderMutantControl::NewGame()
{
	NumberofPeopleAlive = 10;
	NumberSpawned = 0;
	NumberMutants = 0;
	TotalSpawn = 10;
	SpawnTimerAmount = 30.0f;
}

void LanderMutantControl::NewLevelWave()
{
	if (TotalSpawn < 30)
		TotalSpawn += 5;

	NumberSpawned = 0;
}

void LanderMutantControl::EndOfLevelWave()
{
	NumberofPeopleAlive = 0;

	for (auto &person : People)
	{
		if (person.Enabled)
		{
			NumberofPeopleAlive++;
		}

		person.Destroy();
	}

	Score->AddToScore(NumberofPeopleAlive * (100 * Data->Wave));
}

void LanderMutantControl::PlayerHitReset()
{
	int landersAlive = 0;
	int mutantsAlive = 0;
	int peopleAlive = 0;

	for (const auto& lander : Landers)
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

	for (const auto& mutant : Mutants)
	{
		for (auto &shot : mutant->Shots)
		{
			shot.Enabled = false;
		}

		if (mutant->Enabled)
		{
			mutantsAlive++;
			mutant->Reset();
		}
	}

	for (auto &person : People)
	{
		person.Reset();

		if (person.Enabled)
		{
			peopleAlive++;
		}
	}

	NumberSpawned -= landersAlive;
	NumberMutants = mutantsAlive;
	NumberofPeopleAlive = peopleAlive;
}