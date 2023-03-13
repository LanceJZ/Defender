#include "Pod.h"

Pod::Pod()
{

}

Pod::~Pod()
{
}

void Pod::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void Pod::SetRadar(Model model, Texture2D texture)
{
	Radar.SetModel(model, texture);
}

void Pod::SetPlayer(Player* player)
{
	Radar.SetPlayer(player);
}

bool Pod::Initialize()
{
	Model3D::Initialize();

	Radar.Initialize();
	Mirror.Initialize();
	ModelScale = 5;
	Radar.ModelScale = 4;
	Enabled = false;

	return false;
}

bool Pod::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	Mirror.SetModel(TheModel, ModelScale);
	Mirror.BeginRun(camera);
	Radar.BeginRun(camera);

	return false;
}

void Pod::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	Mirror.PositionUpdate(Enabled, X(), Y());
	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);

}

void Pod::Draw()
{
	Model3D::Draw();

	if (!Enabled)
		return;

	Mirror.Draw();
	Radar.Draw();
}

void Pod::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
}
