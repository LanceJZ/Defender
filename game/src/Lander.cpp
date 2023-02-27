#include "Lander.h"

Lander::Lander()
{
	ShotTimer = new Timer();

	for (int i = 0; i < 4; i++)
	{
		Shots[i] = new EnemyShot();
	}
}

Lander::~Lander()
{
}

void Lander::SetShotModel(Model model, Texture2D texture)
{
	for (auto shot : Shots)
	{
		shot->LoadModel(model, texture);
		ShotMirrorR = shot->TheModel;
	}
}

bool Lander::Initialize()
{
	Model3D::Initialize();

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
	}

	MirrorR = TheModel;
	MirrorL = TheModel;

	return false;
}

void Lander::Input()
{

}

void Lander::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
	ShotTimer->Update(deltaTime);

	for (auto shot : Shots)
	{
		shot->Update(deltaTime);
	}

	if (ShotTimer->Elapsed())
	{
		ShotTimer->Reset();
		FireShot();
	}

	if (Y() < (-GetScreenHeight() * 0.25f) + GroundHoverY)
	{
		Velocity.y = 0;
	}

	CheckPlayfieldSidesWarp(4.0f, 3.0f);
}

void Lander::Draw()
{
	Model3D::Draw();

	//(-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i) land size i = 0 to 6;
	float mirror = 7.0f;

	DrawModel(MirrorR, { X() + GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
	DrawModel(MirrorL, { X() - GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);

	for (auto shot : Shots)
	{
		shot->Draw();
	}
}

void Lander::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	ShotTimer->Reset(GetRandomFloat(1.1f, 1.75f));

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
	if (!Shots[0]->Enabled)
	{
		Vector3 vel = GetRandomVelocity(105);

		Shots[0]->Spawn(Position, vel, 8);
	}
}

void Lander::FireShots() //When Lander lowers to grab human, shoots four at a time, four times as rapid.
{

}
