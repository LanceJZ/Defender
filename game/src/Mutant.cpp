#include "Mutant.h"

Mutant::Mutant()
{
}

Mutant::~Mutant()
{
	Explosion = nullptr;
}

bool Mutant::Initialize()
{
	Enemy::Initialize();

	Radius = 14.0f;

	return false;
}

bool Mutant::BeginRun(Camera* camera)
{
	Enemy::BeginRun(camera);

	SetSoundVolume(ShotSound, 1.5f);

	return false;
}

void Mutant::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (Enabled)
	{
		ChangeSpeedTimer.Update(deltaTime);

		if (ShotTimer.Elapsed())
		{
			ShotTimer.Reset(GetRandomFloat(0.3f, 1.5f));
			FireShot();
		}

		ScreenEdgeBoundY(GetScreenHeight() * 0.161f, GetScreenHeight() * 0.015f);
		ChasePlayer();
	}
}

void Mutant::Draw()
{
	Enemy::Draw();

}

void Mutant::Spawn(Vector3 position)
{
	Enemy::Spawn(position);

	GotNearPlayer = false;
	BackToToporBottom = false;
	ShotTimer.Reset(GetRandomFloat(0.3f, 1.5f));
	ChangeSpeedTimer.Reset(GetRandomFloat(0.1f, 0.3f));
}

void Mutant::FireShot()
{
	Enemy::FireShot();
}

void Mutant::ChasePlayer()
{
	if (ChangeSpeedTimer.Elapsed())
	{
		Speed = GetRandomFloat(150.0f, 350.0f);
		ChangeSpeedTimer.Reset(GetRandomFloat(0.05f, 0.1f));
	}

	float worldW = GetScreenWidth() * 3.5f;
	float playerX = ThePlayer->X();
	float shipX = X();

	if (shipX - playerX > worldW || playerX - shipX > worldW)
	{
		if (playerX < X())
		{
			Velocity.x = Speed;
		}
		else
		{
			Velocity.x = -Speed;
		}
	}
	else
	{
		if (playerX < X())
		{
			Velocity.x = -Speed;
		}
		else
		{
			Velocity.x = Speed;
		}
	}

	float distanceY = GetRandomFloat(100.0f, 150.0f);

	if (GotNearPlayer && !BackToToporBottom)
	{
		if (ThePlayer->Y() + distanceY < Y())
		{
			Velocity.y = -Speed * 0.25f;
		}
		else if (ThePlayer->Y() - distanceY > Y())
		{
			Velocity.y = Speed * 0.25f;
		}

		if (ThePlayer->X() + (GetScreenWidth() * 0.5f) < X() || ThePlayer->X() + (-GetScreenWidth() * 0.5f) > X())
		{
			BackToToporBottom = true;
		}
	}

	if (BackToToporBottom)
	{
		if (Y() > 0)
		{
			Velocity.y = Speed * 0.25f;
		}
		else
		{
			Velocity.y = -Speed * 0.25f;
		}

		if (Y() > GetScreenHeight() * 0.333f || Y() < -GetScreenHeight() * 0.45f)
		{
			BackToToporBottom = false;
			Velocity.y = 0;
		}
	}

	float distanceX = GetRandomFloat(75.0f, 100.0f);

	if (playerX < X() + distanceX && playerX > X() - distanceX)
	{
		GotNearPlayer = true;
	}
}

bool Mutant::CheckCollision()
{
	if (Enemy::CheckCollision())
	{

	}

	return false;
}