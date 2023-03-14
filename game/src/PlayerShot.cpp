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

	Tail->Initialize();

	Radius = 3.5f;
	LifeTimer->Set(1);
	RotationAxis.y = 1.0f;
	ModelScale = 3.0f;
	Enabled = false;

	Tail->RotationVelocity = 40.666f;
	Tail->RotationAxis.x = 1.0f;
	Tail->Position.x = -5.5f;
	Tail->ModelScale = 5.0f;
	Tail->Enabled = false;

	return false;
}

void PlayerShot::SetTailModel(Model model)
{
	Tail->TheModel = model;
}

bool PlayerShot::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	Tail->BeginRun(camera);
	AddChild(Tail);

	return false;
}

void PlayerShot::spawn(Vector3 position, Vector3 velocity, bool reverse)
{
	Enabled = true;
	Tail->Enabled = true;
	LifeTimer->Reset();
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
}

void PlayerShot::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
	Tail->Update(deltaTime);
	LifeTimer->Update(deltaTime);

	if (LifeTimer->Elapsed())
	{
		Enabled = false;
		Tail->Enabled = false;
	}
}

void PlayerShot::Draw()
{
	Model3D::Draw();
	Tail->Draw();
}