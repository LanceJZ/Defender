#include "Person.h"

Person::~Person()
{
}

void Person::SetRadar(Model model)
{
	Radar.TheModel = model;
}

void Person::SetPlayer(Player* player)
{
	ThePlayer = player;
	Radar.SetPlayer(player);
}

bool Person::Initialize()
{
	Model3D::Initialize();

	Mirror.Initialize();
	Radar.Initialize();
	ModelScale = 5;
	Radar.ModelScale = 4;
	Enabled = false;

	return false;
}

bool Person::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	Mirror.SetModel(TheModel, ModelScale);
	Mirror.BeginRun(camera);
	Radar.BeginRun(camera);

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