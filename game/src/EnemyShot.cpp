#include "EnemyShot.h"

EnemyShot::~EnemyShot()
{
}

void EnemyShot::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

bool EnemyShot::Initialize()
{
	Model3D::Initialize();

	ModelScale = 3;
	Radius = 2;
	Enabled = false;

	return false;
}

bool EnemyShot::BeginRun()
{
	MirrorR = TheModel;
	MirrorL = TheModel;

	return false;
}

void EnemyShot::Input()
{

}

void EnemyShot::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
	LifeTimer->Update(deltaTime);

	if (LifeTimer->Elapsed())
	{
		Enabled = false;
	}

	if (ScreenEdgeBoundY(GetScreenHeight() * 0.15f, 0))
	{
		Enabled = false;
	}
}

void EnemyShot::Draw()
{
	Model3D::Draw();

	float mirror = 7.0f;

	DrawModel(MirrorR, { X() + GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
	DrawModel(MirrorL, { X() - GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
}

void EnemyShot::Spawn(Vector3 position, Vector3 velocity, float life)
{
	Enabled = true;
	LifeTimer->Reset(life);
	Position = position;
	Velocity = velocity;
}
