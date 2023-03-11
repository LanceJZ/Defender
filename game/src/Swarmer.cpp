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

void Swarmer::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void Swarmer::SetShotModel(Model model, Texture2D texture)
{
	for (auto shot : Shots)
	{
		shot->SetModel(model, texture);
	}
}

void Swarmer::SetRadar(Model model, Texture2D texture)
{
	Radar.SetModel(model, texture);
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

	ModelScale = 5;
	Radar.ModelScale = 4;
	Enabled = false;

	return false;
}

bool Swarmer::BeginRun()
{
	for (auto shot : Shots)
	{
		shot->BeginRun();
	}

	Mirror.SetModel(TheModel, ModelScale);
	Radar.BeginRun();

	return false;
}

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

	if (!Enabled)
		return;

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