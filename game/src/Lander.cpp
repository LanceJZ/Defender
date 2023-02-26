#include "Lander.h"

Lander::Lander()
{
	ShotTimer = new Timer();
}

Lander::~Lander()
{
}

void Lander::SetShotModel(Model model, Texture2D texture)
{
	Shot.LoadModel(model, texture);
	ShotMirrorR = Shot.TheModel;
}

bool Lander::Initialize()
{
	Model3D::Initialize();

	Shot.Initialize();
	ShotTimer->Set(5);
	ModelScale = 14;
	Radius = 14;

	return false;
}

bool Lander::BeginRun()
{
	Shot.BeginRun();
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

	Shot.Update(deltaTime);

	if (ShotTimer->Elapsed())
	{
		ShotTimer->Reset();
		FireShot();
	}

	if (Y() < (-GetScreenHeight() * 0.3f) + GroundHoverY)
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

	DrawLine3D({ (float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

	DrawLine3D({ -(float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{-(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

	Shot.Draw();
}

void Lander::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	ShotTimer->Reset();

	float velX = 0;

	if (GetRandomValue(0, 10) < 5)
	{
		velX = GetRandomFloat(30, 60);
	}
	else
	{
		velX = GetRandomFloat(-60, -30);
	}

	float velY = GetRandomFloat(-20, -10);
	Velocity = { velX, velY, 0 };
	GroundHoverY = GetRandomFloat(-20, 80);
}

void Lander::FireShot()
{

}
