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
	RotationVelocity = GetRandomFloat(25.1f, 52.6f);

	return true;
}

void Baiter::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (Enabled)
	{
		AfterSpawnTimer.Update(deltaTime);

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

		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
	}
}

void Baiter::Draw()
{
	Enemy::Draw();

}

void Baiter::Spawn(Vector3 position, float xVelocity)
{
	Enemy::Spawn(position);

	Velocity.x = xVelocity;

	AfterSpawnTimer.Reset(GetRandomFloat(0.5f, 1.0f));
	ShotTimer.Reset(GetRandomFloat(0.275f, 0.4375f));
	SpeedChangeTimer.Reset(GetRandomFloat(0.75f, 1.5f));
}

void Baiter::Reset()
{
	Enemy::Reset();

}

void Baiter::AfterSpawnMovement()
{
	float percentChange = 0.25f;

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
	XVelocity = ThePlayer->Velocity.x * 1;
	YVelocity = ThePlayer->Velocity.y * 1;
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
