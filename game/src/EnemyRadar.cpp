#include "EnemyRadar.h"

EnemyRadar::EnemyRadar()
{
}

EnemyRadar::~EnemyRadar()
{
}

void EnemyRadar::SetModel(Model model)
{
	Model3D::TheModel = model;
}

void EnemyRadar::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool EnemyRadar::Initialize()
{
	Model3D::Initialize();
	Enabled = false;

	return false;
}

bool EnemyRadar::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	TheCamera = camera;

	return false;
}

void EnemyRadar::PositionUpdate(bool enabled, Vector3 position)
{
	Position = position;
	Enabled = enabled;

	UpdateRadar();
}

void EnemyRadar::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	UpdateRadar();
}

void EnemyRadar::Draw()
{
	Model3D::Draw();

}

void EnemyRadar::UpdateRadar()
{
	float comp = 0.062f;
	float ww = 3.5f;
	float swww = (GetScreenWidth() * ww);
	float swcalc = swww * comp;
	float swwwcalc = (swww * 2) * comp;

	X(TheCamera->position.x + (-ThePlayer->X() * comp) + (X() * comp));

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
