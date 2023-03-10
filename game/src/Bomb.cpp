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
	MirrorL.TheModel = TheModel;
	MirrorL.ModelScale = ModelScale;
	MirrorR.TheModel = TheModel;
	MirrorR.ModelScale = ModelScale;

	return false;
}

void Bomb::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	LifeTimer->Update(deltaTime);

	if (LifeTimer->Elapsed())
		Enabled = false;

	MirrorUpdate(); //Add a common Mirror Update Method.

}

void Bomb::Draw()
{
	Model3D::Draw();

}

void Bomb::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
	LifeTimer->Reset(GetRandomFloat(6.66f, 16.66f));
}

void Bomb::MirrorUpdate()
{
	if (X() > GetScreenWidth() * 2.75f)
	{
		MirrorL.Draw();
	}
	else if (X() < -GetScreenWidth() * 2.75f)
	{
		MirrorR.Draw();
	}
}
