#include "Lander.h"

Lander::Lander()
{
	for (int i = 0; i < 4; i++)
	{
		Shots[i] = new EnemyShot();
	}
}

Lander::~Lander()
{
}

void Lander::SetShotModel(Model model)
{
	for (auto shot : Shots)
	{
		shot->TheModel = model;
	}
}

void Lander::SetRadarModel(Model model)
{
	Radar.TheModel = model;
}

void Lander::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);

	for (auto shot : Shots)
	{
		shot->SetPlayer(ThePlayer);
	}
}

void Lander::SetCamera(Camera* camera)
{
	Radar.SetCamera(camera);
}

bool Lander::Initialize()
{
	Model3D::Initialize();
	Radar.Initialize();
	Mirror.Initialize();

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	ShotTimer->Set(1);
	ModelScale = 14;
	Radius = 14;

	return false;
}

bool Lander::BeginRun()
{
	for (auto shot : Shots)
	{
		shot->BeginRun();
		shot->SetPlayer(ThePlayer);
	}

	Mirror.SetModel(TheModel, ModelScale);
	Radar.ModelScale = 2;
	Radar.BeginRun();
	Mirror.BeginRun();

	return false;
}

void Lander::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
	ShotTimer->Update(deltaTime);

	for (auto shot : Shots)
	{
		shot->Update(deltaTime);
	}

	if (!Enabled)
		return;

	if (ShotTimer->Elapsed())
	{
		if (CurrentMode != FoundPersonMan)
		{
			FireShot();
		}
		else
		{
			FireShots();
		}

	}

	if (CurrentMode == GoingToGround)
	{
		GoToGround();
	}
	else if (CurrentMode == Seek)
	{
		SeekPersonMan();
	}
	else if (CurrentMode == FoundPersonMan)
	{
		FoundPersonManGoingDown();
	}
	else if (CurrentMode == PickUpPersonMan)
	{
		GrabPersonMan();
	}
	else if (CurrentMode == Mutate)
	{
		SpawnMutatant();
	}

	CheckPlayfieldSidesWarp(4.0f, 3.0f);
	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);
	Mirror.PositionUpdate(Enabled, X(), Y());
}

void Lander::Draw()
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

void Lander::Spawn(Vector3 position)
{
	Enabled = true;
	CurrentMode = GoingToGround;
	Position = position;
	ShotTimer->Reset(GetRandomFloat(1.1f, 1.75f));
	PersonCaptured = nullptr;

	float velX = 0;

	if (GetRandomValue(0, 10) < 5)
	{
		velX = GetRandomFloat(30, 60);
	}
	else
	{
		velX = GetRandomFloat(-60, -30);
	}

	float velY = GetRandomFloat(-30, -20);
	Velocity = { velX, velY, 0 };
	GroundHoverY = GetRandomFloat(-20, 80);
}

void Lander::FireShot()
{
	ShotTimer->Reset(GetRandomFloat(1.1f, 1.75f));

	if (!Shots[0]->Enabled)
	{
		Shots[0]->Spawn(Position, VelocityFromAngleZ(Shots[0]->GetShotAngle(Position), 125.0f), 8.0f);
	}
}

void Lander::FireShots()
{
	ShotTimer->Reset(GetRandomFloat(0.275f, 0.4375f));

	for (auto shot : Shots)
	{
		if (!shot->Enabled)
		{
			shot->Spawn(Position, VelocityFromAngleZ(Shots[0]->GetShotAngle(Position), 125.0f), 8.0f);
			return;
		}
	}
}

void Lander::GoToGround()
{
	if (Y() < (-GetScreenHeight() * 0.2f) + GroundHoverY)
	{
		CurrentMode = Seek;
		Velocity.y = 0;
	}
}

void Lander::SeekPersonMan()
{
	for (auto person : People)
	{
		if (person->X() < X() + 25.0f && person->X() > X() - 25.0f)
		{
			if (person->BeingCaptured)
				return;

			CurrentMode = FoundPersonMan;
			ShotTimer->Reset(GetRandomFloat(0.275f, 0.4375f));
			Velocity.x = 0;
			Velocity.y = GetRandomFloat(-60, -40);
			PersonCaptured = person;
			person->BeingCaptured = true;
			return;
		}
	}
}

void Lander::FoundPersonManGoingDown()
{
	if (X() != PersonCaptured->X())
	{
		if (X() > PersonCaptured->X())
		{
			Velocity.x = -10;
		}
		else if (X() < PersonCaptured->X())
		{
			Velocity.x = 10;
		}
		else if (X() == PersonCaptured->X())
		{
			Velocity.x = 0;
		}
	}

	if (Y() + 25 > PersonCaptured->Y() && Y() - 25 < PersonCaptured->Y())
	{
		CurrentMode = PickUpPersonMan;
		Velocity.y = GetRandomFloat(40, 60);
		Velocity.x = 0;
	}
}

void Lander::GrabPersonMan()
{
	if (Y() > GetScreenHeight() * 0.333f)
	{
		CurrentMode = Mutate;
		return;
	}

	PersonCaptured->Y(Y() -25);
}

void Lander::SpawnMutatant()
{
	MutateLander = true;
	Velocity.y = 0;
	PersonCaptured->Enabled = false;
	Enabled = false;
}