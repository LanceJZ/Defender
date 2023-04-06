#include "Pod.h"

Pod::Pod()
{

}

Pod::~Pod()
{
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


	if (Enabled)
	{
		CheckPlayfieldSidesWarp(4.0f, 3.0f);
		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
	}
}

void Pod::Draw()
{
	Enemy::Draw();

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

void Pod::Hit()
{
	Enemy::Hit();

	BeenHit = true;
}

bool Pod::CheckCollision()
{
	if (Enemy::CheckCollision())
	{
		Hit();
	}

	return false;
}

void Pod::Destroy()
{
	Enemy::Destroy();

}
