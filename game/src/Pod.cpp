#include "Pod.h"

Pod::Pod()
{

}

Pod::~Pod()
{
}

void Pod::SetModel(Model model)
{
	Model3D::TheModel = model;
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

bool Pod::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();
	ModelScale = 1.0f;
	Enabled = false;

	return false;
}

bool Pod::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;
	RadarMirror.SetMirrorModel(TheModel, ModelScale);
	RadarMirror.BeginRun(camera);

	SpawnSwarmers(1);

	return false;
}

void Pod::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	RadarMirror.PositionUpdate(Enabled, Position);

	for (auto swarmer : Swarmers)
	{
		swarmer->Update(deltaTime);
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

void Pod::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
}

void Pod::SpawnSwarmers(int count)
{
	for (int i = 0; i < count; i++)
	{
		Swarmers.push_back(new Swarmer());
	}

	for (auto swarmer : Swarmers)
	{
		swarmer->Initialize();
		swarmer->SetModel(SwarmerModel);
		swarmer->SetRadar(SwarmerRadarModel);
		swarmer->SetShotModel(ShotModel);
		swarmer->SetPlayer(ThePlayer);
		swarmer->BeginRun(TheCamera);
		swarmer->Spawn({ 50.0f, 150.0f, 0 });
	}
}
