#include "Pod.h"

Pod::Pod()
{

}

Pod::~Pod()
{
	for (int i = 0; i < Swarmers.size(); i++)
	{
		delete Swarmers[i];
	}

	Swarmers.clear();
	Data = nullptr;
	Explosion = nullptr;
}

bool Pod::Initialize()
{
	Enemy::Initialize();

	Enabled = false;
	Radius = 14.0f;

	return false;
}

void Pod::SetShotModel(Model model)
{
	ShotModel = model;
}

void Pod::SetSwarmerModel(Model model)
{
	SwarmerModel = model;
}

void Pod::SetSwarmerRadarModel(Model model)
{
	SwarmerRadarModel = model;
}

void Pod::SetSwarmerExplodeSound(Sound sound)
{
	SwarmerExplodeSound = sound;
}

void Pod::SetData(SharedData* data)
{
	Data = data;
}

bool Pod::BeginRun(Camera* camera)
{
	Enemy::BeginRun(camera);

	return false;
}

void Pod::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	for (auto swarmer : Swarmers)
	{
		swarmer->Update(deltaTime);
	}

	if (Enabled)
	{
		CheckPlayfieldSidesWarp(4.0f, 3.0f);
		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
		CheckCollision();
	}
}

void Pod::Draw()
{
	Enemy::Draw();

	for (auto swarmer : Swarmers)
	{
		swarmer->Draw();
	}
}

void Pod::Spawn(Vector3 position, float xVol)
{
	Enemy::Spawn(position);

	float rX = GetRandomFloat(-0.95f, 0.95f);
	float rY = GetRandomFloat(-0.95f, 0.95f);
	float rZ = GetRandomFloat(-0.95f, 0.95f);
	RotationAxis = { rX, rY, rZ };
	RotationVelocity = GetRandomFloat(1.5f, 3.5f);

	float minY = 30;
	float maxY = 40;
	float yVol = GetRandomFloat(minY, maxY);

	if (GetRandomValue(0, 100) < 50)
	{
		Velocity.y = -yVol;
	}
	else
	{
		Velocity.y = yVol;
	}

	if (GetRandomValue(0, 100) < 50)
	{
		Velocity.x = -xVol;
	}
	else
	{
		Velocity.x = xVol;
	}
}

void Pod::Reset()
{
	Enemy::Reset();
}

void Pod::SpawnSwarmers(int count)
{

	for (int i = 0; i < count; i++)
	{
		bool spawnNew = true;
		int swarmerSpawnNumber = (int)Swarmers.size();
		int swarmerNumber = 0;
		float xVol = GetRandomFloat(65.0f, 75.0f);
		float yVol = GetRandomFloat(55.0f, 65.0f);

		for (auto swarmer : Swarmers)
		{
			if (!swarmer->Enabled)
			{
				spawnNew = false;
				swarmerSpawnNumber = swarmerNumber;
				break;
			}

			swarmerNumber++;
		}

		if (spawnNew)
		{
			Swarmers.push_back(new Swarmer());
			Swarmers[swarmerSpawnNumber]->Initialize();
			Swarmers[swarmerSpawnNumber]->SetModel(SwarmerModel, 10.0f);
			Swarmers[swarmerSpawnNumber]->SetRadarModel(SwarmerRadarModel, 3.0f);
			Swarmers[swarmerSpawnNumber]->SetShotModel(ShotModel);
			Swarmers[swarmerSpawnNumber]->SetSounds(ShotSound, SwarmerExplodeSound);
			Swarmers[swarmerSpawnNumber]->SetPlayer(ThePlayer);
			Swarmers[swarmerSpawnNumber]->SetExplosion(Explosion);
			Swarmers[swarmerSpawnNumber]->SetScore(Score, 150);
			Swarmers[swarmerSpawnNumber]->BeginRun(TheCamera);
		}

		Swarmers[swarmerSpawnNumber]->Spawn(Position, { xVol, yVol, 0 });
	}


}

bool Pod::CheckCollision()
{
	if (Enemy::CheckCollision())
	{
		PlaySound(ExplodeSound);
		SpawnSwarmers(4 + Data->Wave);
	}

	return false;
}

void Pod::Destroy()
{
	Enemy::Destroy();

}
