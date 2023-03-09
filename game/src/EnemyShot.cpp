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

	if (!Enabled)
		return;

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

	if (Enabled)
		DrawMirror();
}

void EnemyShot::Spawn(Vector3 position, Vector3 velocity, float life)
{
	Enabled = true;
	LifeTimer->Reset(life);
	Position = position;
	Velocity = velocity;
}

void EnemyShot::DrawMirror()
{
	float mirror = 7.0f;

	if (X() > GetScreenWidth() * 2.75f)
	{
		DrawModel(MirrorL, { X() - GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
	}
	else if (X() < -GetScreenWidth() * 2.75f)
	{
		DrawModel(MirrorR, { X() + GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
	}
}
