#include "EnemyShot.h"

EnemyShot::EnemyShot()
{
	LifeTimer = new Timer();

}

EnemyShot::~EnemyShot()
{
}

void EnemyShot::SetModel(Model model, Texture2D texture)
{
	LoadModel(model, texture);
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
}

void EnemyShot::Draw()
{
	Model3D::Draw();

}

void EnemyShot::Spawn(Vector3 position, Vector3 velocity, float life)
{
	Enabled = true;
	LifeTimer->Reset(life);
	Position = position;
	Velocity = velocity;
}
