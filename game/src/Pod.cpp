#include "Pod.h"

Pod::Pod()
{

}

Pod::~Pod()
{
	for (int i = 0; i < PodsSwarmers.size(); i++)
	{
		delete PodsSwarmers[i];
	}

	PodsSwarmers.clear();
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

	for (auto swarmer : PodsSwarmers)
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

	for (auto swarmer : PodsSwarmers)
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
		int swarmerSpawnNumber = (int)PodsSwarmers.size();
		int swarmerNumber = 0;
		float xVol = GetRandomFloat(65.0f, 75.0f);
		float yVol = GetRandomFloat(55.0f, 65.0f);

		for (auto swarmer : PodsSwarmers)
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
			PodsSwarmers.push_back(new Swarmer());
			PodsSwarmers[swarmerSpawnNumber]->Initialize();
			PodsSwarmers[swarmerSpawnNumber]->SetModel(SwarmerModel, 10.0f);
			PodsSwarmers[swarmerSpawnNumber]->SetRadarModel(SwarmerRadarModel, 3.0f);
			PodsSwarmers[swarmerSpawnNumber]->SetShotModel(ShotModel);
			PodsSwarmers[swarmerSpawnNumber]->SetSounds(ShotSound, SwarmerExplodeSound);
			PodsSwarmers[swarmerSpawnNumber]->SetPlayer(ThePlayer);
			PodsSwarmers[swarmerSpawnNumber]->SetExplosion(Explosion);
			PodsSwarmers[swarmerSpawnNumber]->SetScore(Score, 150);
			PodsSwarmers[swarmerSpawnNumber]->BeginRun(TheCamera);
		}

		PodsSwarmers[swarmerSpawnNumber]->Spawn(Position, { xVol, yVol, 0 });
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
