#include "Person.h"

Person::~Person()
{
}

void Person::SetRadar(Model model)
{
	RadarMirror.SetRadarModel(model, 4.0f);
}

void Person::SetPlayer(Player* player)
{
	ThePlayer = player;
	RadarMirror.SetPlayer(player);
}

bool Person::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();
	ModelScale = 5.0f;
	Radius = 7.0f;
	Enabled = false;

	return false;
}

bool Person::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	RadarMirror.SetMirrorModel(TheModel, ModelScale);
	RadarMirror.BeginRun(camera);

	return false;
}

void Person::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	RadarMirror.Enabled = Enabled;

	if (Enabled)
	{
		if (GoingDown)
		{
			Falling();
		}

		if (CaughtByPlayer)
		{
			GoingForARide();
		}

		RadarMirror.PositionUpdate(Enabled, Position);
	}
}

void Person::Draw()
{
	Model3D::Draw();

	RadarMirror.Draw();
}

void Person::Spawn(Vector3 position)
{
	Position = position;
	Enabled = true;
	BeingCaptured = false;
	GoingDown = false;
	CaughtByPlayer = false;
}

void Person::Dropped()
{
	DroppedY = Y();
	BeingCaptured = false;
	GoingDown = true;
	Acceleration.y = -0.150f;
}

void Person::Falling()
{
	CheckCollision();

	if (CaughtByPlayer)
	{
		return;
	}

	if (Velocity.y < -60.0f)
	{
		Acceleration.y = 0;
	}

	if (Y() < -(GetScreenHeight() / 2.10f))
	{
		Velocity.y = 0;
		GoingDown = false;

		if (DroppedY > 0)
		{
			Enabled = false;
		}
	}
}

void Person::GoingForARide()
{
	X(ThePlayer->X());
	Y(ThePlayer->Y() - 25.0f);

	if (Y() < -(GetScreenHeight() / 2.10f))
	{
		CaughtByPlayer = false;
	}
}

void Person::CheckCollision()
{
	if (CirclesIntersect(ThePlayer))
	{
		CaughtByPlayer = true;
		GoingDown = false;
		Velocity.y = 0;
		Acceleration.y = 0;
	}
}
