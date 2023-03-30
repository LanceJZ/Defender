#include "BomberControl.h"

BomberControl::BomberControl()
{
}

BomberControl::~BomberControl()
{
	for (int i = 0; i < Bombers.size(); i++)
	{
		delete Bombers[i];
	}

	Bombers.clear();

	UnloadModel(BomberModel);
	UnloadModel(BombModel);
	UnloadModel(BomberRadarModel);
	Explosion = nullptr;

	UnloadSound(ExplosionSound);
}

bool BomberControl::Initialize()
{

	return false;
}

void BomberControl::SetBomber(Model model)
{
	BomberModel = model;
}

void BomberControl::SetBomb(Model model)
{
	BombModel = model;
}

void BomberControl::SetBomberRadar(Model model)
{
	BomberRadarModel = model;
}

void BomberControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void BomberControl::SetData(SharedData* data)
{
	Data = data;
}

void BomberControl::SetExplosion(ExplosionControl* explosion)
{
	Explosion = explosion;
}

void BomberControl::SetSounds(Sound explosion)
{
	ExplosionSound = explosion;
}

void BomberControl::SetScore(ScoreKeeper* score)
{
	Score = score;
}

bool BomberControl::BeginRun(Camera* camera)
{
	TheCamera = camera;
	return false;
}

void BomberControl::Update(float deltaTime)
{
	Data->BombersBeGone = true;

	for (auto bomber : Bombers)
	{
		bomber->Update(deltaTime);

		if (bomber->Enabled)
		{
			Data->BombersBeGone = false;
		}
	}
}

void BomberControl::Draw()
{
	for (auto bomber : Bombers)
	{
		bomber->Draw();
	}
}

void BomberControl::NewWave()
{
	if (Data->Wave > 0)
	{
		SpawnBombers(Data->Wave);
		Data->BombersBeGone = false;
	}
}

void BomberControl::Reset()
{
	int spawnAmount = 0;

	for (auto bomber : Bombers)
	{
		if (bomber->Enabled)
		{
			Data->BombersBeGone = false;
			spawnAmount++;
			bomber->Enabled = false;

			for (auto &bomb : bomber->Shots)
			{
				bomb.Enabled = false;
			}
		}
	}

	SpawnBombers(spawnAmount);
}

void BomberControl::SpawnBombers(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		int spawnNumber = (int)Bombers.size();
		int bomberCount = 0;
		bool spawnNew = true;

		for (auto bomber : Bombers)
		{
			if (!bomber->Enabled)
			{
				spawnNumber = bomberCount;
				spawnNew = false;
				break;
			}

			bomberCount++;
		}

		if (spawnNew)
		{
			Bombers.push_back(new Bomber());
			Bombers[spawnNumber]->Initialize();
			Bombers[spawnNumber]->SetModel(BomberModel, 10.0f);
			Bombers[spawnNumber]->SetBomb(BombModel);
			Bombers[spawnNumber]->SetRadarModel(BomberRadarModel, 3.0f);
			Bombers[spawnNumber]->SetPlayer(ThePlayer);
			Bombers[spawnNumber]->SetExplosion(Explosion);
			Bombers[spawnNumber]->SetSounds(ShotSound, ExplosionSound);
			Bombers[spawnNumber]->SetScore(Score, 250);
			Bombers[spawnNumber]->BeginRun(TheCamera);
		}

		float xLine = GetRandomFloat(GetScreenWidth() * 2.5f, GetScreenWidth() * 3.5f);
		float xVol = GetRandomFloat(-75, -25);
		Bombers[spawnNumber]->Spawn({xLine + GetRandomFloat(-100, 100),
			GetRandomFloat(-GetScreenHeight() * 0.5f, GetScreenHeight() * 0.5f), 0}, xVol);
	}
}
