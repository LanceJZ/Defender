#include "PodSwarmerControl.h"

PodSwarmerControl::PodSwarmerControl()
{
}

PodSwarmerControl::~PodSwarmerControl()
{
	for (int i = 0; i < Pods.size(); i++)
	{
		delete Pods[i];
	}

	Pods.clear();

	for (int i = 0; i < Swarmers.size(); i++)
	{
		delete Swarmers[i];
	}

	Swarmers.clear();

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

bool PodSwarmerControl::Initialize()
{

	return false;
}

void PodSwarmerControl::SetPodModel(Model model)
{
	PodModel = model;
}

void PodSwarmerControl::SetSwarmerModel(Model model)
{
	SwarmerModel = model;
}

void PodSwarmerControl::SetShotModel(Model model)
{
	ShotModel = model;
}

void PodSwarmerControl::SetPodRadarModel(Model model)
{
	PodRadarModel = model;
}

void PodSwarmerControl::SetSwarmerRadarModel(Model model)
{
	SwarmerRadarModel = model;
}

void PodSwarmerControl::SetSounds(Sound explodeSound, Sound swarmerExplode,
	Sound shotSound)
{
	PodExplodeSound = explodeSound;
	SwarmerShotSound = shotSound;
	SwarmerExplodeSound = swarmerExplode;
}

void PodSwarmerControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void PodSwarmerControl::SetData(SharedData* data)
{
	Data = data;
}

void PodSwarmerControl::SetExplosion(ExplosionControl* explosion)
{
	Explosion = explosion;
}

void PodSwarmerControl::SetScore(ScoreKeeper* score)
{
	Score = score;
}

bool PodSwarmerControl::BeginRun(Camera* camera)
{
	TheCamera = camera;

	return false;
}

void PodSwarmerControl::Update(float deltaTime)
{
	Data->PodsSwarmersBeGone = true;

	for (auto pod : Pods)
	{
		pod->Update(deltaTime);


		if (pod->BeenHit)
		{
			pod->BeenHit = false;
			SpawnSwarmers(pod->Position, 4 + Data->Wave);
		}

		if (pod->Enabled)
		{
			Data->PodsSwarmersBeGone = false;
		}
	}

	for (auto swarmer : Swarmers)
	{
		for (auto swarmer : Swarmers)
		{
			if (swarmer->Enabled)
			{
				Data->PodsSwarmersBeGone = false;
			}
		}

		swarmer->Update(deltaTime);
	}
}

void PodSwarmerControl::Draw()
{
	for (auto pod : Pods)
	{
		pod->Draw();
	}

	for (auto swarmer : Swarmers)
	{
		swarmer->Draw();
	}
}

void PodSwarmerControl::NewWave()
{
	if (Data->Wave > 0)
	{
		SpawnPods(Data->Wave);
		Data->PodsSwarmersBeGone = false;
	}
}

void PodSwarmerControl::Reset()
{
	int spawnAmount = 0;

	for (auto pod : Pods)
	{
		if (pod->Enabled)
		{
			pod->Position.y = GetScreenWidth() * 3.5f;
			Data->PodsSwarmersBeGone = false;
		}

		for (auto swarmer : Swarmers)
		{
			swarmer->Position.y = GetScreenWidth() * 3.5f;
			Data->PodsSwarmersBeGone = false;
		}
	}
}

void PodSwarmerControl::SpawnPods(int count)
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

		Sound noSound = { 0 };

		if (spawnNew)
		{
			Pods.push_back(new Pod());
			Pods[spawnNumber]->Initialize();
			Pods[spawnNumber]->SetModel(PodModel, 10.0f);
			Pods[spawnNumber]->SetRadarModel(PodRadarModel, 3.0f);
			Pods[spawnNumber]->SetShotModel(ShotModel);
			Pods[spawnNumber]->SetSounds(noSound, PodExplodeSound);
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
			Pods[spawnNumber]->Spawn({ xLine + GetRandomFloat(-200.0f, 200.0f), y, 0 },
				xVol);
		}
	}
}

void PodSwarmerControl::SpawnSwarmers(Vector3 position, int count)
{
	for (int i = 0; i < count; i++)
	{
		bool spawnNew = true;
		int swarmerSpawnNumber = (int)Swarmers.size();
		int swarmerNumber = 0;
		float xVol = GetRandomFloat(65.0f, 75.0f);
		float yVol = GetRandomFloat(55.0f, 65.0f);

		for (auto swarmer : Swarmers)
		{
			if (!swarmer->Enabled)
			{
				spawnNew = false;
				swarmerSpawnNumber = swarmerNumber;
				break;
			}

			swarmerNumber++;
		}

		if (spawnNew)
		{
			Swarmers.push_back(new Swarmer());
			Swarmers[swarmerSpawnNumber]->Initialize();
			Swarmers[swarmerSpawnNumber]->SetModel(SwarmerModel, 10.0f);
			Swarmers[swarmerSpawnNumber]->SetRadarModel(SwarmerRadarModel, 3.0f);
			Swarmers[swarmerSpawnNumber]->SetShotModel(ShotModel);
			Swarmers[swarmerSpawnNumber]->SetSounds(SwarmerShotSound,
				SwarmerExplodeSound);
			Swarmers[swarmerSpawnNumber]->SetPlayer(ThePlayer);
			Swarmers[swarmerSpawnNumber]->SetExplosion(Explosion);
			Swarmers[swarmerSpawnNumber]->SetScore(Score, 150);
			Swarmers[swarmerSpawnNumber]->BeginRun(TheCamera);
		}

		Swarmers[swarmerSpawnNumber]->Spawn(position, { xVol, yVol, 0 });
	}
}
