#include "SwarmerControl.h"

SwarmerControl::SwarmerControl()
{
}

SwarmerControl::~SwarmerControl()
{
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

bool SwarmerControl::Initialize()
{

	return false;
}

bool SwarmerControl::BeginRun(Camera* camera)
{
	TheCamera = camera;

	SpawnPods(1);

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

	for (auto pod : Pods)
	{
		pod->Initialize();
		pod->SetModel(PodModel);
		pod->SetRadar(PodRadarModel);
		pod->BeginRun(TheCamera);
		pod->SetPlayer(ThePlayer);
		pod->Spawn({ 200.0f, 200.0f, 0 });
	}
}
