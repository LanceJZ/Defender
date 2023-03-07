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

void Mutant::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void Mutant::SetShotModel(Model model, Texture2D texture)
{
	for (auto shot : Shots)
	{
		shot->SetModel(model, texture);
	}
}

void Mutant::SetRadarModel(Model model, Texture2D texture)
{
	Radar.SetModel(model, texture);
}

void Mutant::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);
}

void Mutant::SetCamera(Camera* camera)
{
	Radar.SetCamera(camera);
}

bool Mutant::Initialize()
{
	Model3D::Initialize();

	ModelScale = 14;
	Radius = 14;

	return false;
}

bool Mutant::BeginRun()
{
	MirrorL.TheModel = TheModel;
	MirrorL.ModelScale = ModelScale;
	MirrorR.TheModel = TheModel;
	MirrorR.ModelScale = ModelScale;
	Radar.ModelScale = 2;

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
	MirrorUpdate();
	ChasePlayer();
}

void Mutant::Draw()
{
	Model3D::Draw();

	if (!Enabled)
		return;

	MirrorL.Draw();
	MirrorR.Draw();
	Radar.Draw();
}

void Mutant::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	ShotTimer->Reset(GetRandomFloat(0.3f, 1.5f));
}

void Mutant::FireShot()
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


	if (!Shots[0]->Enabled)
	{
		Shots[0]->Spawn(Position, VelocityFromAngleZ(angle, 150.0f), 7.5f);
	}
}

float Mutant::AimedShot()
{
	float percentChance = GetRandomFloat(0.0f, 0.05f);

	Vector3 aimv = ThePlayer->Position;
	aimv.x += ThePlayer->Velocity.x;

	return AngleFromVectorZ(aimv) + GetRandomFloat(-percentChance, percentChance);
}

void Mutant::MirrorUpdate()
{
	float mirror = 7.0f;
	MirrorL.X(X() - GetScreenWidth() * mirror);
	MirrorL.Y(Y());
	MirrorL.Enabled = Enabled;
	MirrorR.X(X() + GetScreenWidth() * mirror);
	MirrorR.Y(Y());
	MirrorR.Enabled = Enabled;
}

void Mutant::ChasePlayer()
{
	float speed = GetRandomFloat(90.0f, 150.0f);

	if (ThePlayer->X() < X())
	{
		Velocity.x = -speed;
	}
	else
	{
		Velocity.x = speed;
	}

	if (ThePlayer->Y() + 100.0f < Y())
	{
		Velocity.y = -speed * 0.75f;
	}
	else if (ThePlayer->Y() - 100 > Y())
	{
		Velocity.y = speed * 0.75f;
	}
}