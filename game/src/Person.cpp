#include "Person.h"

Person::Person()
{
}

Person::~Person()
{
	ThePlayer = nullptr;
}

bool Person::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();
	Radius = 7.0f;

	return false;
}

void Person::SetRadar(Model &model)
{
	RadarMirror.SetRadarModel(model, 4.0f);
}

void Person::SetPlayer(Player* player)
{
	ThePlayer = player;
	RadarMirror.SetPlayer(player);
}

bool Person::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	RadarMirror.SetMirrorModel(GetModel(), ModelScale);
	RadarMirror.BeginRun(camera);

	return false;
}

void Person::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (Enabled)
	{
		if (State == GoingDown)
		{
			Falling();
		}

		if (State == CaughtByPlayer)
		{
			GoingForARide();
		}

		RadarMirror.PositionUpdate(Enabled, Position);
	}
	else
	{
		RadarMirror.EnabledUpdate(Enabled);
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
	Velocity.y = 0;
	Acceleration.y = 0;
	Enabled = true;
	State = OnGround;
}

void Person::Dropped()
{
	DroppedY = Y();
	State = GoingDown;
	Acceleration.y = -0.150f;
}

void Person::Falling()
{
	CheckCollision();

	if (State == CaughtByPlayer)
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
		Acceleration.y = 0;
		State = OnGround;

		if (DroppedY > 0)
		{
			Destroy();
		}
	}
}

void Person::GoingForARide()
{
	X(ThePlayer->X());
	Y(ThePlayer->Y() - 25.0f);

	if (Y() < -(GetScreenHeight() / 2.10f))
	{
		State = OnGround;
	}
}

void Person::CheckCollision()
{
	if (CirclesIntersect(ThePlayer))
	{
		State = CaughtByPlayer;
		Velocity.y = 0;
		Acceleration.y = 0;
	}
}

void Person::Destroy()
{
	Enabled = false;
	CountChanged = true;
}

void Person::Reset()
{
	Velocity.y = 0;
	Acceleration.y = 0;
	Y(-(GetScreenHeight() / 2.10f));
	State = OnGround;
}
