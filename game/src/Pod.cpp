#include "Pod.h"

Pod::Pod()
{

}

Pod::~Pod()
{
	Swarmers.clear();
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

void Pod::SetData(SharedData* data)
{
	Data = data;
}

bool Pod::BeginRun(Camera* camera)
{
	Enemy::BeginRun(camera);

	TheCamera = camera;

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
		Swarmers.push_back(new Swarmer());
	}

	float xVol = GetRandomFloat(65.0f, 75.0f);
	float yVol = GetRandomFloat(55.0f, 65.0f);

	for (auto swarmer : Swarmers)
	{
		swarmer->Initialize();
		swarmer->SetModel(SwarmerModel, 10.0f);
		swarmer->SetRadarModel(SwarmerRadarModel, 3.0f);
		swarmer->SetShotModel(ShotModel);
		swarmer->SetPlayer(ThePlayer);
		swarmer->BeginRun(TheCamera);
		swarmer->Spawn(Position, { xVol, yVol, 0 });
	}
}

bool Pod::CheckCollision()
{
	if (Enemy::CheckCollision())
	{
		SpawnSwarmers(4 + Data->Wave);
	}

	return false;
}

void Pod::Destroy()
{
	Enemy::Destroy();

}
