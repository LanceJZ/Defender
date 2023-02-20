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

	ModelScale = 10;

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

}

void EnemyShot::Draw()
{
	Model3D::Draw();

}

void EnemyShot::Spawn(Vector3 position)
{
	Enabled = true;
	LifeTimer->Reset();
	Position = position;

}
