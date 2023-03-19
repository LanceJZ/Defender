#include "Swarmer.h"

Swarmer::Swarmer()
{
	for (int i = 0; i < 4; i++)
	{
		Shots[i] = new EnemyShot();
	}
}

Swarmer::~Swarmer()
{
}

bool Swarmer::Initialize()
{
	Model3D::Initialize();

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	RadarMirror.Initialize();
	ModelScale = 10.0f;
	Enabled = false;

	return false;
}

void Swarmer::SetShotModel(Model model)
{
	for (auto shot : Shots)
	{
		shot->SetModel(model);
	}
}

void Swarmer::SetRadar(Model model)
{
	RadarMirror.SetRadarModel(model, 5.0f);
}

void Swarmer::SetPlayer(Player* player)
{
	ThePlayer = player;
	RadarMirror.SetPlayer(player);

	for (auto shot : Shots)
	{
		shot->SetPlayer(ThePlayer);
	}
}

bool Swarmer::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	RotationAxis = { 0, 1.0f, 0 };
	RotationVelocity = GetRandomFloat(25.1f, 52.6f);

	for (auto shot : Shots)
	{
		shot->BeginRun(camera);
	}

	TheCamera = camera;
	RadarMirror.SetMirrorModel(GetModel(), ModelScale);
	RadarMirror.BeginRun(camera);

	return false;
}
// Swarmer don't change X direction until they are half screen distance away.
// Can not shoot opposite direction of movement.
// Take a second to change Y direction of movement after passing player Y position.
// They shot 1/4 screen width distance in front of themselves at your Y position.
// When Pod is shot, Swarmers head towards the player.
void Swarmer::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	for (auto shot : Shots)
	{
		shot->Update(deltaTime);
	}

	ShotTimer.Update(deltaTime);

	if (ShotTimer.Elapsed())
	{
		FireShot();
	}

	AfterSpawn.Update(deltaTime);

	if (AfterSpawn.Elapsed())
	{
		AfterSpawnMovement();
	}

	if (Enabled)
	{
		CheckPlayfieldSidesWarp(4.0f, 3.0f);
		CheckPlayfieldHeightWarp(-0.15f, 1.0f);
		RadarMirror.PositionUpdate(Enabled, Position);
	}
	else
	{
		RadarMirror.EnabledUpdate(Enabled);
	}
}

void Swarmer::Draw()
{
	Model3D::Draw();

	for (auto shot : Shots)
	{
		shot->Draw();
	}

	RadarMirror.Draw();
}

void Swarmer::Spawn(Vector3 position, Vector3 velocity)
{
	Enabled = true;
	Position = position;
	Velocity = velocity;
	XVolocity = velocity.x;
	YVolocity = velocity.y;
	RotationAxis = { 0, 1, 0 };
	RotationVelocity = 20.5f;

	if (XVolocity < 0)
	{
		XVolocity *= -1;
	}

	if (GetRandomValue(1, 100) < 50)
	{
		Velocity.x *= -1;
	}

	if (GetRandomValue(1, 100) < 50)
	{
		Velocity.y *= -1;
	}

	ShotTimer.Reset(GetRandomFloat(0.25f, 0.35f));
	AfterSpawn.Reset(GetRandomFloat(0.25f, 0.5f));
}

void Swarmer::FireShot()
{
	ShotTimer.Reset(GetRandomFloat(0.275f, 0.4375f));

	if (Velocity.x > 0)
	{
		if (ThePlayer->X() < X())
		{
			return;
		}
	}
	else
	{
		if (ThePlayer->X() > X())
		{
			return;
		}
	}

	for (auto shot : Shots)
	{
		if (!shot->Enabled)
		{
			shot->Spawn(Position, VelocityFromAngleZ(Shots[0]->GetShotAngle(Position), 155.0f), 7.0f);
			return;
		}
	}
}

void Swarmer::AfterSpawnMovement()
{
	if (ThePlayer->X() + (WindowWidth * 0.75f) < X())
	{
		Velocity.x = -XVolocity;
	}
	else if (ThePlayer->X() - (WindowWidth * 0.75f) > X())
	{
		Velocity.x = XVolocity;
	}

	float distanceX = GetRandomFloat(200.0f, 250.0f);
	float distanceY = GetRandomFloat(25.0f, 50.0f);

	if (ThePlayer->X() < X() + distanceX && ThePlayer->X() > X() - distanceX)
	{
		if (ThePlayer->Y() + distanceY < Y())
		{
			Velocity.y = -YVolocity;
		}
		else if (ThePlayer->Y() - distanceY > Y())

		{
			Velocity.y = YVolocity;
		}
	}
}