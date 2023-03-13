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