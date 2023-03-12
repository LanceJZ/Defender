#include "Mutant.h"

Mutant::Mutant()
{
	for (int i = 0; i < 4; i++)
	{
		Shots[i] = new EnemyShot();
	}
}

Mutant::~Mutant()
{
}

void Mutant::SetShotModel(Model model)
{
	for (auto shot : Shots)
	{
		shot->TheModel = model;
	}
}

void Mutant::SetRadarModel(Model model)
{
	Radar.TheModel = model;
}

void Mutant::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);

	for (auto shot : Shots)
	{
		shot->SetPlayer(ThePlayer);
	}
}

void Mutant::SetCamera(Camera* camera)
{
	Radar.SetCamera(camera);
}

bool Mutant::Initialize()
{
	Model3D::Initialize();

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	ModelScale = 14;
	Radius = 14;

	return false;
}

bool Mutant::BeginRun()
{
	for (auto shot : Shots)
	{
		shot->BeginRun();
	}

	Mirror.SetModel(TheModel, ModelScale);
	Radar.ModelScale = 2;
	Radar.BeginRun();

	return false;
}

void Mutant::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	for (auto shot : Shots)
	{
		shot->Update(deltaTime);
	}

	if (!Enabled)
		return;

	ShotTimer->Update(deltaTime);
	ChangeSpeedTimer->Update(deltaTime);

	if (ShotTimer->Elapsed())
	{
		ShotTimer->Reset();
		FireShot();
	}

	CheckPlayfieldSidesWarp(4.0f, 3.0f);
	ScreenEdgeBoundY(GetScreenHeight() * 0.161f, GetScreenHeight() * 0.015f);
	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);
	ChasePlayer();
	Mirror.PositionUpdate(Enabled, X(), Y());
}

void Mutant::Draw()
{
	Model3D::Draw();

	for (auto shot : Shots)
	{
		shot->Draw();
	}

	if (!Enabled)
		return;

	Mirror.Draw();
	Radar.Draw();
}

void Mutant::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	ShotTimer->Reset(GetRandomFloat(0.3f, 1.5f));
	ChangeSpeedTimer->Reset(GetRandomFloat(0.1f, 0.3f));
}

void Mutant::FireShot()
{
	if (!Shots[0]->Enabled)
	{
		Shots[0]->Spawn(Position, VelocityFromAngleZ(Shots[0]->GetShotAngle(Position), 350.0f), 4.5f);
	}
}

void Mutant::ChasePlayer()
{
	if (ChangeSpeedTimer->Elapsed())
	{
		Speed = GetRandomFloat(150.0f, 350.0f);
		ChangeSpeedTimer->Reset(GetRandomFloat(0.05f, 0.1f));
	}

	float worldW = GetScreenWidth() * 3.5f;
	float playerX = ThePlayer->X();
	float shipX = X();

	float shiplessplayer = shipX - playerX;
	float playerlessship = playerX - shipX;

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

	if (GotNearPlayer)
	{
		if (ThePlayer->Y() + 100.0f < Y())
		{
			Velocity.y = -Speed * 0.25f;
		}
		else if (ThePlayer->Y() - 100 > Y())
		{
			Velocity.y = Speed * 0.25f;
		}
	}

	if (playerX < X() + 75.0f && playerX > X() - 75.0)
	{
		GotNearPlayer = true;
	}
}
