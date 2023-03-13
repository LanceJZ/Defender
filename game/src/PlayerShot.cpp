#include "PlayerShot.h"

PlayerShot::PlayerShot()
{
	LifeTimer = new Timer();
	Tail = new Model3D();
}

PlayerShot::~PlayerShot()
{
}

bool PlayerShot::Initialize()
{
	Model3D::Initialize();

	ModelScale = 5.0f;
	Radius = 5.5f;
	Enabled = false;
	LifeTimer->Set(1);
	RotationAxis.y = 1;

	Tail->RotationVelocity = 40.666f;
	Tail->RotationAxis.x = 1;
	Tail->Position.x = -7;
	Tail->ModelScale = 5.0f;
	Tail->Enabled = false;

	AddChild(Tail);

	return false;
}

void PlayerShot::SetTailModel(Model model)
{
	Tail->TheModel = model;
}

void PlayerShot::Load()
{

}

bool PlayerShot::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	return false;
}

void PlayerShot::spawn(Vector3 position, Vector3 velocity, bool reverse)
{
	Enabled = true;
	Tail->Enabled = true;
	LifeTimer->Reset();
	Position = position;
	Velocity.x = velocity.x * 0.1f;
	Velocity.y = velocity.y * 0.1f;

	if (reverse)
	{
		Velocity.x -= 200;
		Position.x -= 40;
	}
	else
	{
		Velocity.x += 200;
		Position.x += 40;
	}

	Velocity.x *= 10;

	if (reverse)// Make tail child of shot. Have it rotate separate from shot.
	{
		Rotation = PI;
	}
	else
	{
		Rotation = 0;
	}
}

void PlayerShot::Input()
{

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