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

void Swarmer::SetModel(Model model)
{
	Swarmer::TheModel = model;
}

void Swarmer::SetShotModel(Model model)
{
	for (auto shot : Shots)
	{
		shot->TheModel = model;
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
	RadarMirror.SetMirrorModel(TheModel, ModelScale);
	RadarMirror.BeginRun(camera);

	return false;
}
// Swarmer don't change Y direction until they are half screen distance away.
// Can not shoot opposite direction of movement.
// Take a second to change X direction of movement after passing player Y position.
// They shot 1/4 screen width distance in front of themselves at your Y position.
// When Pod is shot, Swarmers head towards the player.
void Swarmer::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	for (auto shot : Shots)
	{
		shot->Update(deltaTime);
	}

	ShotTimer->Update(deltaTime);

	if (ShotTimer->Elapsed())
	{
		ShotTimer->Reset();
		FireShot();
	}

	RadarMirror.PositionUpdate(Enabled, Position);
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

void Swarmer::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
}

void Swarmer::FireShot()
{
	if (!Shots[0]->Enabled)
	{
		Shots[0]->Spawn(Position, VelocityFromAngleZ(Shots[0]->GetShotAngle(Position), 350.0f), 4.5f);
	}
}