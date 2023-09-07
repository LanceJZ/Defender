#include "Baiter.h"

Baiter::Baiter()
{
}

Baiter::~Baiter()
{
}

bool Baiter::Initialize()
{
	Enemy::Initialize();

	return true;
}

bool Baiter::BeginRun(Camera* camera)
{
	Enemy::BeginRun(camera);

	RotationAxis = { 0, 1.0f, 0 };
	RotationVelocity = GetRandomFloat(15.1f, 22.6f);

	return true;
}

void Baiter::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (Enabled)
	{
		AfterSpawnTimer.Update(deltaTime);
		SpeedChangeTimer.Update(deltaTime);
		ShotTimer.Update(deltaTime);

		if (AfterSpawnTimer.Elapsed())
		{
			AfterSpawnMovement();
			AfterSpawnTimer.Reset();
		}

		if (SpeedChangeTimer.Elapsed())
		{
			ChangeSpeed();
			SpeedChangeTimer.Reset();
		}

		if (ShotTimer.Elapsed())
		{
			ShotTimer.Reset(GetRandomFloat(1.1275f, 2.3724375f));
			FireShot();
		}

		CheckPlayfieldSidesWarp(4.0f, 3.0f);
		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
	}
}

void Baiter::Draw()
{
	Enemy::Draw();

}

void Baiter::Spawn()
{
	Enemy::Spawn({ ThePlayer->X(),  -(float)GetScreenHeight() + 15, 0});

	ChangeSpeed();

	Velocity.x = ThePlayer->Velocity.x * -1;

	AfterSpawnTimer.Reset(GetRandomFloat(2.5f, 4.0f));
	ShotTimer.Reset(GetRandomFloat(0.435f, 0.6375f));
	SpeedChangeTimer.Reset(GetRandomFloat(2.75f, 5.5f));
}

void Baiter::Reset()
{
	Enemy::Reset();

}

void Baiter::AfterSpawnMovement()
{
	float percentChange = 0.5f;

	if (ThePlayer->X() + (WindowWidth * percentChange) < X())
	{
		Velocity.x = -XVelocity;
	}
	else if (ThePlayer->X() - (WindowWidth * percentChange) > X())
	{
		Velocity.x = XVelocity;
	}

	if (ThePlayer->Y() + (WindowHeight * percentChange) < Y())
	{
		Velocity.y = -YVelocity;
	}
	else if (ThePlayer->Y() - (WindowHeight * percentChange) > Y())
	{
		Velocity.y = YVelocity;
	}
}

void Baiter::ChangeSpeed()
{
	float multiplier = 1.0f;
	XVelocity = ThePlayer->Velocity.x * multiplier;

	if (Y() > 0)
	{
		YVelocity = GetRandomFloat(-30, -20);
	}
	else
	{
		YVelocity = GetRandomFloat(20, 30);
	}
}

void Baiter::FireShot()
{
	Enemy::FireShot();

	ShotTimer.Reset(GetRandomFloat(0.275f, 0.4375f));
}

bool Baiter::CheckCollision()
{
	return false;
}

void Baiter::Destroy()
{
	Enemy::Destroy();

}
