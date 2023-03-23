#include "Bomb.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

bool Bomb::Initialize()
{
	Model3D::Initialize();

	Mirror.Initialize();

	return false;
}

bool Bomb::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	Mirror.SetModel(GetModel(), ModelScale);
	Mirror.BeginRun(camera);

	return false;
}

void Bomb::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	LifeTimer.Update(deltaTime);

	if (LifeTimer.Elapsed())
	{
		Enabled = false;
	}

	Mirror.PositionUpdate(Enabled, Position);
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
	LifeTimer.Reset(GetRandomFloat(6.66f, 16.66f));
}