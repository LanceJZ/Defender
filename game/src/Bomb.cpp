#include "Bomb.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

bool Bomb::Initialize()
{
	Model3D::Initialize();

	ModelScale = 15;

	return false;
}

bool Bomb::BeginRun()
{
	Mirror.SetModel(TheModel, ModelScale);

	return false;
}

void Bomb::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	LifeTimer->Update(deltaTime);

	if (LifeTimer->Elapsed())
		Enabled = false;

	Mirror.PositionUpdate(Enabled, X(), Y());
}

void Bomb::Draw()
{
	Model3D::Draw();

	Mirror.Draw();
}

void Bomb::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	Mirror.PositionUpdate(Enabled, X(), Y());
	LifeTimer->Reset(GetRandomFloat(6.66f, 16.66f));
}