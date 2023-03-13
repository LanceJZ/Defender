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

void Swarmer::SetShotModel(Model model)
{
	for (auto shot : Shots)
	{
		shot->TheModel = model;
	}
}

void Swarmer::SetRadar(Model model)
{
	Radar.TheModel = model;
}

void Swarmer::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);

	for (auto shot : Shots)
	{
		shot->SetPlayer(ThePlayer);
	}
}

void Swarmer::SetCamera(Camera* camera)
{
	TheCamera = camera;
	Radar.SetCamera(camera);
}

bool Swarmer::Initialize()
{
	Model3D::Initialize();

	for (auto shot : Shots)
	{
		shot->Initialize();
	}

	Radar.Initialize();
	Mirror.Initialize();
	ModelScale = 5;
	Radar.ModelScale = 4;
	Enabled = false;

	return false;
}

bool Swarmer::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	for (auto shot : Shots)
	{
		shot->BeginRun(camera);
	}

	Mirror.SetModel(TheModel, ModelScale);
	Mirror.BeginRun(camera);
	Radar.BeginRun(camera);

	return false;
}
// Swarmer don't change Y direction until they are half screen distance away.
// Can not shoot opposite direction of movement.
// Take a second to change X direction of movement after passing player Y position.
// They shot 1/4 screen width distance in front of themselves at your Y position.
// Up to four Pods at wave start, starting with wave three with two.
// Four Swarmers per Pod. When Pod is shot, Swarmers head towards the player.
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

	Mirror.PositionUpdate(Enabled, X(), Y());
	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);
}

void Swarmer::Draw()
{
	Model3D::Draw();

	for (auto shot : Shots)
	{
		shot->Draw();
	}

	Mirror.Draw();
	Radar.Draw();
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