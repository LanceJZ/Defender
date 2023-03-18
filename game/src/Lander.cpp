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

void Lander::SetModel(Model model)
{
	TheModel = model;
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
	RadarMirror.SetRadarModel(model, 3.0f);
}

void Lander::SetPlayer(Player* player)
{
	ThePlayer = player;
	RadarMirror.SetPlayer(player);

	for (auto shot : Shots)
	{
		shot->SetPlayer(ThePlayer);
	}
}

bool Lander::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	ShotTimer->Set(1);
	ModelScale = 14;
	Radius = 14;

	return false;
}

bool Lander::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	for (auto shot : Shots)
	{
		shot->BeginRun(camera);
		shot->SetPlayer(ThePlayer);
	}

	RadarMirror.SetMirrorModel(TheModel, ModelScale);
	RadarMirror.BeginRun(camera);

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
	RadarMirror.PositionUpdate(Enabled, Position);
	CheckCollision();
}

void Lander::Draw()
{
	Model3D::Draw();

	for (auto shot : Shots)
	{
		shot->Draw();
	}

	RadarMirror.Draw();
}

void Lander::Spawn(Vector3 position)
{
	Enabled = true;
	CurrentMode = GoingToGround;
	Position = position;
	ShotTimer->Reset(GetRandomFloat(1.1f, 1.75f));
	PersonCaptured = nullptr;

	float velX = 0;

	if (GetRandomValue(0, 100) < 50)
	{
		velX = GetRandomFloat(30.0f, 60.0f);
	}
	else
	{
		velX = GetRandomFloat(-60.0f, -30.0f);
	}

	float velY = GetRandomFloat(-30.0f, -20.0f);
	Velocity = { velX, velY, 0 };
	GroundHoverY = GetRandomFloat(-20.0f, 80.0f);
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

void Lander::CheckCollision()
{
	if (CirclesIntersect(ThePlayer))
	{
		Distroy();
		return;
	}

	for (auto shot : ThePlayer->Shots)
	{
		if (CirclesIntersect(shot))
		{
			Distroy();
			return;
		}
	}
}

void Lander::Distroy()
{
	Enabled = false;
	RadarMirror.Enabled = false;
	CountChange = true;

	if (PersonCaptured)
	{
		PersonCaptured->Dropped();
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
		if (person->Enabled)
		{
			if (person->X() < X() + 25.0f && person->X() > X() - 25.0f)
			{
				if (person->BeingCaptured)
					return;

				CurrentMode = FoundPersonMan;
				ShotTimer->Reset(GetRandomFloat(0.275f, 0.4375f));
				Velocity.x = 0;
				Velocity.y = GetRandomFloat(-40.0f, -30.0f);
				PersonCaptured = person;
				person->BeingCaptured = true;
				return;
			}
		}
	}
}

void Lander::FoundPersonManGoingDown()
{
	if (X() != PersonCaptured->X())
	{
		if (X() > PersonCaptured->X())
		{
			Velocity.x = -10.0f;
		}
		else if (X() < PersonCaptured->X())
		{
			Velocity.x = 10.0f;
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

	PersonCaptured->Y(Y() -25.0f);
}

void Lander::SpawnMutatant()
{
	Velocity.y = 0;
	RadarMirror.Enabled = false;
	PersonCaptured->Distroy();
	MutateLander = true;
	Enabled = false;
}