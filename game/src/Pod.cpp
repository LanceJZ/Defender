#include "Pod.h"

Pod::Pod()
{

}

Pod::~Pod()
{
}

bool Pod::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();
	ModelScale = 10.0f;
	Enabled = false;

	return false;
}

void Pod::SetShotModel(Model model)
{
	ShotModel = model;
}

void Pod::SetSwarmerModel(Model model)
{
	SwarmerModel = model;
}

void Pod::SetSwarmerRadarModel(Model model)
{
	SwarmerRadarModel = model;
}

void Pod::SetRadar(Model model)
{
	RadarMirror.SetRadarModel(model, 4.0f);
}

void Pod::SetPlayer(Player* player)
{
	RadarMirror.SetPlayer(player);
	ThePlayer = player;
}

bool Pod::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;
	RadarMirror.SetMirrorModel(GetModel(), ModelScale);
	RadarMirror.BeginRun(camera);

	return false;
}

void Pod::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	for (auto swarmer : Swarmers)
	{
		swarmer->Update(deltaTime);
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

void Pod::Draw()
{
	Model3D::Draw();

	RadarMirror.Draw();

	for (auto swarmer : Swarmers)
	{
		swarmer->Draw();
	}
}

void Pod::Spawn(Vector3 position, float xVol)
{
	Enabled = true;
	Position = position;
	RotationAxis = { 0.5f, 0.95f, 0.25f }; //Make random
	RotationVelocity = 2.5f;

	float minY = 30;
	float maxY = 40;
	float yVol = GetRandomFloat(minY, maxY);

	if (GetRandomValue(0, 10) < 5)
	{
		Velocity.y = -yVol;
	}
	else
	{
		Velocity.y = yVol;
	}

	if (GetRandomValue(0, 10) < 5)
	{
		Velocity.x = -xVol;
	}
	else
	{
		Velocity.x = xVol;
	}
}

void Pod::SpawnSwarmers(int count)
{
	for (int i = 0; i < count; i++)
	{
		Swarmers.push_back(new Swarmer());
	}

	float xLine = GetRandomFloat(-400.0f, 400.0f);
	float xVol = GetRandomFloat(65.0f, 75.0f);
	float yVol = GetRandomFloat(55.0f, 65.0f);

	for (auto swarmer : Swarmers)
	{
		swarmer->Initialize();
		swarmer->SetModel(SwarmerModel);
		swarmer->SetRadar(SwarmerRadarModel);
		swarmer->SetShotModel(ShotModel);
		swarmer->SetPlayer(ThePlayer);
		swarmer->BeginRun(TheCamera);
		swarmer->Spawn({ xLine, 150.0f, 0 }, { xVol, yVol, 0 });
	}
}
