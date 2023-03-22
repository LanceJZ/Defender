#include "PlayerShot.h"

PlayerShot::PlayerShot()
{
}

PlayerShot::~PlayerShot()
{
}

bool PlayerShot::Initialize()
{
	Model3D::Initialize();

	Tail.Initialize();

	Radius = 3.5f;
	LifeTimer.Set(0.5666f);
	RotationAxis.y = 1.0f;
	ModelScale = 3.0f;
	Enabled = false;

	Tail.RotationVelocity = 40.666f;
	Tail.RotationAxis.x = 1.0f;
	Tail.Position.x = -5.5f;
	Tail.ModelScale = 5.0f;
	Tail.Enabled = false;

	Mirror.Initialize();

	return false;
}

void PlayerShot::SetTailModel(Model model)
{
	Tail.SetModel(model);
}

bool PlayerShot::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	Tail.BeginRun(camera);
	AddChild(&Tail);

	Mirror.SetModel(Tail.GetModel(), Tail.ModelScale);
	Mirror.BeginRun(camera);

	return false;
}

void PlayerShot::Spawn(Vector3 position, Vector3 velocity, bool reverse)
{
	Enabled = true;
	Tail.Enabled = true;
	LifeTimer.Reset();
	Position = position;
	Velocity.x = velocity.x;
	Velocity.y = velocity.y * 0.1f;

	if (reverse)
	{
		Velocity.x -= 2000.0f;
		Position.x -= 40.0f;
		Rotation = PI;
	}
	else
	{
		Velocity.x += 2000.0f;
		Position.x += 40.0f;
		Rotation = 0;
	}

	Mirror.PositionUpdate(Enabled, Position);
}

void PlayerShot::Reset()
{
	Enabled = false;
	Tail.Enabled = false;
}

void PlayerShot::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
	Tail.Update(deltaTime);
	LifeTimer.Update(deltaTime);

	if (LifeTimer.Elapsed())
	{
		Enabled = false;
		Tail.Enabled = false;
	}

	CheckPlayfieldSidesWarp(4.0f, 3.0f);
	Mirror.PositionUpdate(Enabled, Position);
}

void PlayerShot::Draw()
{
	Model3D::Draw();

	Tail.Draw();
	Mirror.Draw();
}