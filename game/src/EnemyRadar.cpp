#include "EnemyRadar.h"

EnemyRadar::EnemyRadar()
{
	TheCamera = nullptr;
	ThePlayer = nullptr;
}

EnemyRadar::~EnemyRadar()
{
}

void EnemyRadar::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

void EnemyRadar::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void EnemyRadar::SetCamera(Camera* camera)
{
	TheCamera = camera;
}

bool EnemyRadar::Initialize()
{
	Model3D::Initialize();

	return false;
}

bool EnemyRadar::BeginRun()
{

	return false;
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
