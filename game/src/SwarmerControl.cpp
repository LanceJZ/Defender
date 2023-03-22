#include "SwarmerControl.h"

SwarmerControl::SwarmerControl()
{
}

SwarmerControl::~SwarmerControl()
{
}

bool SwarmerControl::Initialize()
{

	return false;
}

void SwarmerControl::SetPodModel(Model model)
{
	PodModel = model;
}

void SwarmerControl::SetSwarmerModel(Model model)
{
	SwarmerModel = model;
}

void SwarmerControl::SetShotModel(Model model)
{
	ShotModel = model;
}

void SwarmerControl::SetPodRadarModel(Model model)
{
	PodRadarModel = model;
}

void SwarmerControl::SetSwarmerRadarModel(Model model)
{
	SwarmerRadarModel = model;
}

void SwarmerControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool SwarmerControl::BeginRun(Camera* camera)
{
	TheCamera = camera;

	return false;
}

void SwarmerControl::Update(float deltaTime)
{
	for (auto pod : Pods)
	{
		pod->Update(deltaTime);
	}
}

void SwarmerControl::Draw()
{
	for (auto pod : Pods)
	{
		pod->Draw();
	}
}

void SwarmerControl::SpawnPods(float count)
{
	for (int i = 0; i < count; i++)
	{
		Pods.push_back(new Pod());
	}

	float xLine = 0;

	if (GetRandomValue(1, 10) < 5)
	{
		xLine = GetRandomFloat(GetScreenWidth() * 1.5f, GetScreenWidth() * 3.5f);
	}
	else
	{
		xLine = GetRandomFloat(-GetScreenWidth() * 3.5f, -GetScreenWidth() * 1.5f);
	}

	float xVol = GetRandomFloat(35.0f, 55.5f);
	float y = GetRandomFloat(-GetScreenHeight() * 0.5f, GetScreenHeight() * 0.5f);

	for (auto pod : Pods)
	{
		pod->Initialize();
		pod->SetModel(PodModel, 10.0f);
		pod->SetRadar(PodRadarModel);
		pod->SetShotModel(ShotModel);
		pod->SetSwarmerModel(SwarmerModel);
		pod->SetSwarmerRadarModel(SwarmerRadarModel);
		pod->SetPlayer(ThePlayer);
		pod->BeginRun(TheCamera);
		pod->Spawn({ xLine + GetRandomFloat(-200.0f, 200.0f), y, 0 }, xVol);
	}
}
