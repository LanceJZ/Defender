#include "BomberControl.h"

BomberControl::BomberControl()
{
}

BomberControl::~BomberControl()
{
}

bool BomberControl::Initialize()
{

	return false;
}

void BomberControl::SetBomber(Model model)
{
	BomberModel = model;
}

void BomberControl::SetBomb(Model model)
{
	BombModel = model;
}

void BomberControl::SetBomberRadar(Model model)
{
	BomberRadarModel = model;
}

void BomberControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool BomberControl::BeginRun(Camera* camera)
{
	TheCamera = camera;
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

	float xLine = GetRandomFloat(GetScreenWidth() * 2.5f, GetScreenWidth() * 3.5f);
	float xVol = GetRandomFloat(-75, -25);

	for (auto bomber : Bombers)
	{
		bomber->Initialize();
		bomber->SetModel(BomberModel, 10.0f);
		bomber->SetBomb(BombModel);
		bomber->SetRadarModel(BomberRadarModel, 3.0f);
		bomber->SetPlayer(ThePlayer);
		bomber->BeginRun(TheCamera);
		bomber->Spawn({xLine + GetRandomFloat(-100, 100),
			GetRandomFloat(-GetScreenHeight() * 0.5f, GetScreenHeight() * 0.5f), 0}, xVol);
	}
}
