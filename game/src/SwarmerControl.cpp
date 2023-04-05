#include "SwarmerControl.h"

SwarmerControl::SwarmerControl()
{
}

SwarmerControl::~SwarmerControl()
{
	for (int i = 0; i < Pods.size(); i++)
	{
		delete Pods[i];
	}

	Pods.clear();
	ThePlayer = nullptr;
	TheCamera = nullptr;
	Data = nullptr;
	Explosion = nullptr;

	UnloadModel(PodModel);
	UnloadModel(SwarmerModel);
	UnloadModel(PodRadarModel);
	UnloadModel(SwarmerRadarModel);
	UnloadSound(SwarmerShotSound);
	UnloadSound(SwarmerExplodeSound);
	UnloadSound(PodExplodeSound);
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

void SwarmerControl::SetSounds(Sound explodeSound, Sound swarmerExplode,
	Sound shotSound)
{
	PodExplodeSound = explodeSound;
	SwarmerShotSound = shotSound;
	SwarmerExplodeSound = swarmerExplode;
}

void SwarmerControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void SwarmerControl::SetData(SharedData* data)
{
	Data = data;
}

void SwarmerControl::SetExplosion(ExplosionControl* explosion)
{
	Explosion = explosion;
}

void SwarmerControl::SetScore(ScoreKeeper* score)
{
	Score = score;
}

bool SwarmerControl::BeginRun(Camera* camera)
{
	TheCamera = camera;

	return false;
}

void SwarmerControl::Update(float deltaTime)
{
	Data->PodsSwarmersBeGone = true;

	for (auto pod : Pods)
	{
		pod->Update(deltaTime);

		if (pod->Enabled)
		{
			Data->PodsSwarmersBeGone = false;
		}
		else
		{
			for (auto swarmer : pod->Swarmers)
			{
				if (swarmer->Enabled)
				{
					Data->PodsSwarmersBeGone = false;
				}
			}
		}
	}
}

void SwarmerControl::Draw()
{
	for (auto pod : Pods)
	{
		pod->Draw();
	}
}

void SwarmerControl::NewWave()
{
	if (Data->Wave > 0)
	{
		SpawnPods(Data->Wave);
		Data->PodsSwarmersBeGone = false;
	}
}

void SwarmerControl::Reset()
{
	int spawnAmount = 0;

	for (auto pod : Pods)
	{
		if (pod->Enabled)
		{
			pod->Position.y = GetScreenWidth() * 3.5f;
			Data->PodsSwarmersBeGone = false;
		}

		for (auto swarmer : pod->Swarmers)
		{
			swarmer->Position.y = GetScreenWidth() * 3.5f;
			Data->PodsSwarmersBeGone = false;
		}
	}
}

void SwarmerControl::SpawnPods(int count)
{
	for (int i = 0; i < count; i++)
	{
		int spawnNumber = (int)Pods.size();
		int podCount = 0;
		bool spawnNew = true;

		for (auto pod : Pods)
		{
			if (!pod->Enabled)
			{
				spawnNumber = podCount;
				spawnNew = false;
				break;
			}

			podCount++;
		}

		if (spawnNew)
		{
			Pods.push_back(new Pod());
			Pods[spawnNumber]->Initialize();
			Pods[spawnNumber]->SetModel(PodModel, 10.0f);
			Pods[spawnNumber]->SetRadarModel(PodRadarModel, 3.0f);
			Pods[spawnNumber]->SetShotModel(ShotModel);
			Pods[spawnNumber]->SetSwarmerModel(SwarmerModel);
			Pods[spawnNumber]->SetSwarmerRadarModel(SwarmerRadarModel);
			Pods[spawnNumber]->SetSounds(SwarmerShotSound, PodExplodeSound);
			Pods[spawnNumber]->SetPlayer(ThePlayer);
			Pods[spawnNumber]->SetData(Data);
			Pods[spawnNumber]->SetExplosion(Explosion);
			Pods[spawnNumber]->SetScore(Score, 1000);
			Pods[spawnNumber]->BeginRun(TheCamera);
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
			Pods[spawnNumber]->Spawn({ xLine + GetRandomFloat(-200.0f, 200.0f), y, 0 }, xVol);
		}
	}
}
