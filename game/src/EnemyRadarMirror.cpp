#include "EnemyRadarMirror.h"

EnemyRadarMirror::EnemyRadarMirror()
{
}

EnemyRadarMirror::~EnemyRadarMirror()
{
}

void EnemyRadarMirror::SetRadarModel(Model model, float scale)
{
	Model3D::TheModel = model;
	Model3D::ModelScale = scale;
}

void EnemyRadarMirror::SetMirrorModel(Model model, float scale)
{
	Mirrors.SetModel(model, scale);
}

void EnemyRadarMirror::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool EnemyRadarMirror::Initialize()
{
	Model3D::Initialize();

	Mirrors.Initialize();
	Enabled = false;

	return false;
}

bool EnemyRadarMirror::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	Mirrors.BeginRun(camera);
	TheCamera = camera;

	return false;
}

void EnemyRadarMirror::PositionUpdate(bool enabled, Vector3 position)
{
	Position = position;
	OrgPosition = position;
	Enabled = enabled;

	UpdateRadar();
	Mirrors.PositionUpdate(enabled, position);
}

void EnemyRadarMirror::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
}

void EnemyRadarMirror::Draw()
{
	Model3D::Draw();

	Mirrors.Draw();
}

void EnemyRadarMirror::UpdateRadar()
{
	float comp = 0.062f;
	float ww = 3.5f;
	float swww = (GetScreenWidth() * ww);
	float swcalc = swww * comp;
	float swwwcalc = (swww * 2) * comp;

	X(TheCamera->position.x + (-ThePlayer->X() * comp) + (OrgPosition.x * comp));

	if (X() > TheCamera->position.x + swcalc)
	{
		X(X() - swwwcalc);
	}
	else if (X() < TheCamera->position.x - swcalc)
	{
		X(X() + swwwcalc);
	}

	Y((Y() * 0.148f) + (GetScreenHeight() * 0.4376f));
}