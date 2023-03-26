#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	ThePlayer = nullptr;
	TheCamera = nullptr;
}

bool Enemy::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();

	ShotTimer.Set(GetRandomFloat(1.0f, 2.0f));

	for (auto &shot : Shots)
	{
		shot.Initialize();
	}

	return false;
}

void Enemy::SetRadarModel(Model model, float scale)
{
	RadarMirror.SetRadarModel(model, scale);
}

void Enemy::SetShotModel(Model model)
{
	for (auto& shot : Shots)
	{
		shot.SetModel(model, 3.0f);
	}
}

void Enemy::SetPlayer(Player* player)
{
	ThePlayer = player;
	RadarMirror.SetPlayer(player);

	for (auto &shot : Shots)
	{
		shot.SetPlayer(ThePlayer);
	}
}

void Enemy::SetSounds(Sound &shot, Sound &explode)
{
	ShotSound = shot;
	ExplodeSound = explode;
}

bool Enemy::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;

	RadarMirror.SetMirrorModel(GetModel(), ModelScale);
	RadarMirror.BeginRun(camera);
	SetSoundVolume(ShotSound, 0.25f);

	for (auto &shot : Shots)
	{
		shot.BeginRun(camera);
	}

	return false;
}

void Enemy::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	ShotTimer.Update(deltaTime);

	for (auto &shot : Shots)
	{
		shot.Update(deltaTime);
	}

	if (Enabled)
	{
		RadarMirror.PositionUpdate(Enabled, Position);
		CheckPlayfieldSidesWarp(4.0f, 3.0f);
	}
}

void Enemy::Draw()
{
	Model3D::Draw();

	for (auto &shot : Shots)
	{
		shot.Draw();
	}

	RadarMirror.Draw();
}

bool Enemy::CheckCollision()
{
	if (CirclesIntersect(ThePlayer))
	{
		Destroy();
		ThePlayer->Hit();
		return true;
	}

	for (auto &shot : Shots)
	{
		if (shot.Enabled)
		{
			if (ThePlayer->CirclesIntersect(&shot))
			{
				ThePlayer->Hit();
			}
		}
	}

	for (auto &shot : ThePlayer->Shots)
	{
		if (shot.Enabled)
		{
			if (CirclesIntersect(&shot))
			{
				shot.Enabled = false;
				Destroy();
				return true;
			}
		}
	}

	return false;
}

void Enemy::FireShot()
{
	PlaySound(ShotSound);

	for (auto &shot : Shots)
	{
		if (!shot.Enabled)
		{
			shot.Spawn(Position, VelocityFromAngleZ(Shots[0].GetShotAngle(Position), 125.0f), 8.0f);
			return;
		}
	}
}

void Enemy::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	Velocity = { 0,0,0 };

}

void Enemy::Reset()
{
	for (auto &shot : Shots)
	{
		shot.Enabled = false;
	}

	Destroy();
}

void Enemy::Destroy()
{
	CountChange = true;
	Enabled = false;
	RadarMirror.EnabledUpdate(false);
}