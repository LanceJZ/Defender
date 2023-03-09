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

void Lander::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void Lander::SetShotModel(Model model, Texture2D texture)
{
	for (auto shot : Shots)
	{
		shot->SetModel(model, texture);
	}
}

void Lander::SetRadarModel(Model model, Texture2D texture)
{
	Radar.SetModel(model, texture);
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

	Radar.BeginRun();

	MirrorL.TheModel = TheModel;
	MirrorL.ModelScale = ModelScale;
	MirrorR.TheModel = TheModel;
	MirrorR.ModelScale = ModelScale;
	Radar.ModelScale = 2;

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
		FireShot();
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
	MirrorUpdate();
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

	if (X() > GetScreenWidth() * 2.75f)
	{
		MirrorL.Draw();
	}
	else if (X() < -GetScreenWidth() * 2.75f)
	{
		MirrorR.Draw();
	}

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
	float angle = 0;

	if (GetRandomValue(0, 10) < 5)
	{
		angle = AimedShot();
	}
	else
	{
		angle = GetRandomRadian();
	}

	if (CurrentMode != FoundPersonMan)
	{
		ShotTimer->Reset(GetRandomFloat(1.1f, 1.75f));

		if (!Shots[0]->Enabled)
		{
			Shots[0]->Spawn(Position, VelocityFromAngleZ(angle, 125.0f), 8.0f);
		}
	}
	else
	{
		ShotTimer->Reset(GetRandomFloat(0.275f, 0.4375f));

		for (auto shot : Shots)
		{
			if (!shot->Enabled)
			{
				shot->Spawn(Position, VelocityFromAngleZ(angle, 125.0f), 8.0f);
				return;
			}
		}
	}
}

void Lander::FireShots() //When Lander lowers to grab human, shoots four at a time, four times as rapid.
{

}

float Lander::AimedShot()
{
	float percentChance = GetRandomFloat(0.0f, 0.075f);

	Vector3 aimv = ThePlayer->Position;
	aimv.x += ThePlayer->Velocity.x;

	return AngleFromVectorZ(aimv) + GetRandomFloat(-percentChance, percentChance);
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

void Lander::MirrorUpdate()
{
	float mirror = 7.0f;
	MirrorL.X(X() - GetScreenWidth() * mirror);
	MirrorL.Y(Y());
	MirrorL.Enabled = Enabled;
	MirrorR.X(X() + GetScreenWidth() * mirror);
	MirrorR.Y(Y());
	MirrorR.Enabled = Enabled;
}
