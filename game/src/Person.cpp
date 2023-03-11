#include "Person.h"

Person::~Person()
{
}

void Person::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void Person::SetRadar(Model model, Texture2D texture)
{
	Radar.SetModel(model, texture);
}

void Person::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);
}

void Person::SetCamera(Camera* camera)
{
	TheCamera = camera;
	Radar.SetCamera(camera);
}

bool Person::Initialize()
{
	Model3D::Initialize();
	Radar.Initialize();

	ModelScale = 5;
	Radar.ModelScale = 4;
	Enabled = false;

	return false;
}

bool Person::BeginRun()
{
	Mirror.SetModel(TheModel, ModelScale);
	Radar.BeginRun();

	return false;
}

void Person::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (!Enabled)
		return;

	Mirror.PositionUpdate(Enabled, X(), Y());
	Radar.Position = Position;
	Radar.Enabled = Enabled;
	Radar.Update(deltaTime);
}

void Person::Draw()
{
	Model3D::Draw();

	if (!Enabled)
		return;

	Mirror.Draw();
	Radar.Draw();
}

void Person::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
}