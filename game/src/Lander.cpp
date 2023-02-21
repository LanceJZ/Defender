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

	CheckScreenEdgeY();
	CheckPlayfieldSidesWarp(4.0f, 3.0f);
}

void Lander::Draw()
{
	Model3D::Draw();

	Shot.Draw();
}

void Lander::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	ShotTimer->Reset();
	float velX = GetRandomFloat(-60, 60);
	float velY = GetRandomFloat(-20, 20);
	Velocity = { velX, velY, 0 };
}

void Lander::FireShot()
{

}
