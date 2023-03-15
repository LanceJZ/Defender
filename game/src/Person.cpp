#include "Person.h"

Person::~Person()
{
}

void Person::SetRadar(Model model)
{
	RadarMirror.SetRadarModel(model, 4.0f);
}

void Person::SetPlayer(Player* player)
{
	ThePlayer = player;
	RadarMirror.SetPlayer(player);
}

bool Person::Initialize()
{
	Model3D::Initialize();

	RadarMirror.Initialize();
	ModelScale = 5.0f;
	Enabled = false;

	return false;
}

bool Person::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	RadarMirror.SetMirrorModel(TheModel, ModelScale);
	RadarMirror.BeginRun(camera);

	return false;
}

void Person::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	RadarMirror.PositionUpdate(Enabled, Position);
}

void Person::Draw()
{
	Model3D::Draw();

	RadarMirror.Draw();
}

void Person::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
}