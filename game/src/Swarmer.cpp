#include "Swarmer.h"

Swarmer::Swarmer()
{
}

Swarmer::~Swarmer()
{
	Explosion = nullptr;
}

bool Swarmer::Initialize()
{
	Enemy::Initialize();

	Radius = 6.0f;

	return true;
}

bool Swarmer::BeginRun(Camera* camera)
{
	Enemy::BeginRun(camera);

	//SetSoundVolume(ShotSound, 1.0f);
	RotationAxis = { 0, 1.0f, 0 };
	RotationVelocity = GetRandomFloat(25.1f, 52.6f);

	return true;
}
// Swarmer don't change X direction until they are half screen distance away.
// Can not shoot opposite direction of movement.
// Take a second to change Y direction of movement after passing player Y position.
// They shot 1/4 screen width distance in front of themselves at your Y position.
// When Pod is shot, Swarmers head towards the player after they separate.
void Swarmer::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (Enabled)
	{
		AfterSpawnTimer.Update(deltaTime);

		if (AfterSpawnTimer.Elapsed())
		{
			AfterSpawnMovement();
		}

		if (ShotTimer.Elapsed())
		{
			ShotTimer.Reset(GetRandomFloat(1.1275f, 2.3724375f));
			FireShot();
		}

		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
	}
}

void Swarmer::Draw()
{
	Enemy::Draw();

}

void Swarmer::Spawn(Vector3 position, Vector3 velocity)
{
	Enemy::Spawn(position);

	Velocity = velocity;
	XVelocity = velocity.x;
	YVelocity = velocity.y;
	RotationAxis = { 0, 1, 0 };
	RotationVelocity = 20.5f;

	if (XVelocity < 0)
	{
		XVelocity *= -1;
	}

	if (GetRandomValue(1, 100) < 50)
	{
		Velocity.x *= -1;
	}

	if (GetRandomValue(1, 100) < 50)
	{
		Velocity.y *= -1;
	}

	AfterSpawnTimer.Reset(GetRandomFloat(0.25f, 0.5f));
	ShotTimer.Reset(GetRandomFloat(0.275f, 0.4375f));
}

void Swarmer::Reset()
{
	Enemy::Reset();

}

void Swarmer::Destroy()
{
	Enemy::Destroy();

}

bool Swarmer::CheckCollision()
{
	if (Enemy::CheckCollision())
	{
		PlaySound(ExplodeSound);
		Explosion->Spawn(Position, 10, 1.5f);
	}

	return false;
}

void Swarmer::FireShot()
{
	ShotTimer.Reset(GetRandomFloat(0.275f, 0.4375f));

	if (Velocity.x > 0)
	{
		if (ThePlayer->X() < X())
		{
			return;
		}
	}
	else
	{
		if (ThePlayer->X() > X())
		{
			return;
		}
	}

	Enemy::FireShot();
}

void Swarmer::AfterSpawnMovement()
{
	float percentChange = 0.75f;

	if (ThePlayer->X() + (WindowWidth * percentChange) < X())
	{
		Velocity.x = -XVelocity;
	}
	else if (ThePlayer->X() - (WindowWidth * percentChange) > X())
	{
		Velocity.x = XVelocity;
	}

	if (DistanceTimer.Elapsed())
	{
		DistanceTimer.Reset(GetRandomFloat(0.15f, 0.5f));
		DistanceX = GetRandomFloat(200.0f, 250.0f);
		DistanceY = GetRandomFloat(25.0f, 50.0f);
	}

	if (ThePlayer->X() < X() + DistanceX && ThePlayer->X() > X() - DistanceX)
	{
		if (ThePlayer->Y() + DistanceY < Y())
		{
			Velocity.y = -YVelocity;
		}
		else if (ThePlayer->Y() - DistanceY > Y())

		{
			Velocity.y = YVelocity;
		}
	}
}