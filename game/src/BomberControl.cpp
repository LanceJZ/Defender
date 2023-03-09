#include "BomberControl.h"

BomberControl::BomberControl()
{

}

BomberControl::~BomberControl()
{
}

void BomberControl::SetBomber(Model model, Texture2D texture)
{
	BomberModel = model;
	BomberTexture = texture;
}

void BomberControl::SetBomb(Model model, Texture2D texture)
{
	BombModel = model;
	BombTexture = texture;
}

void BomberControl::SetBomberRadar(Model model, Texture2D texture)
{
	BomberRadarModel = model;
	BomberRadarTexture = texture;
}

void BomberControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void BomberControl::SetCamera(Camera* camera)
{
	TheCamera = camera;
}

bool BomberControl::Initialize()
{

	return false;
}

bool BomberControl::BeginRun()
{
	SpawnBombers(3);
	return false;
}

void BomberControl::Update(float deltaTime)
{
	for (auto bomber : Bombers)
	{
		bomber->Update(deltaTime);
	}
}

void BomberControl::Draw()
{
	for (auto bomber : Bombers)
	{
		bomber->Draw();
	}
}

void BomberControl::SpawnBombers(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Bombers.push_back(new Bomber());
	}

	float xLine = GetRandomFloat(-GetScreenWidth() * 3.5f, GetScreenWidth() * 3.5f);

	for (auto bomber : Bombers)
	{
		bomber->X(xLine + GetRandomFloat(-100, 100));
		bomber->Y(GetRandomFloat(-GetScreenHeight() * 0.3f, GetScreenHeight() * 0.3f));
		bomber->Initialize();
		bomber->SetModel(BomberModel, BomberTexture);
		bomber->SetBomb(BombModel, BombTexture);
		bomber->SetRadar(BomberRadarModel, BomberRadarTexture);
		bomber->SetPlayer(ThePlayer);
		bomber->SetCamera(TheCamera);
		bomber->BeginRun();
		bomber->ModelScale = 10;
	}
}
