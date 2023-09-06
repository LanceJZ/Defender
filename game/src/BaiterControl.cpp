#include "BaiterControl.h"

BaiterControl::BaiterControl()
{

}

BaiterControl::~BaiterControl()
{
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;
	ExplosionControl* Explosion = nullptr;
	ScoreKeeper* Score = nullptr;
	SharedData* Data = nullptr;
}

bool BaiterControl::Initialize()
{
	SpawnTimer.Set(105.666f);
	DownToTimer.Set(300);
	WaveTimer.Set(1800);

	return false;
}

void BaiterControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void BaiterControl::SetModels(Model baiter, Model shot)
{
	BaiterModel = baiter;
	ShotModel = shot;
}

void BaiterControl::SetRadarModel(Model radar)
{
	RadarModel = radar;
}

void BaiterControl::SetSounds(Sound baiter, Sound shot, Sound explode)
{
	BaiterSound = baiter;
	ShotSound = shot;
	ExplosionSound = explode;
}

void BaiterControl::SetExplosion(ExplosionControl* explosion)
{
	Explosion = explosion;
}

void BaiterControl::SetData(SharedData* data)
{
	Data = data;
}

void BaiterControl::SetScore(ScoreKeeper* score)
{
	Score = score;
}

bool BaiterControl::BeginRun(Camera* camera)
{
	TheCamera = camera;
	return false;
}

void BaiterControl::Update(float deltaTime)
{
	SpawnTimer.Update(deltaTime);
	WaveTimer.Update(deltaTime);
	DownToTimer.Update(deltaTime);

	if (IsOn && SpawnTimer.Elapsed())
	{
		SpawnTimer.Reset();
		Spawn();
	}
	else if (IsDown && DownToTimer.Elapsed())
	{
		IsDown = false;
		Activate();
	}
	else if (WaveTimer.Elapsed())
	{
		Activate();
	}

	for (const auto& baiter : Baiters)
	{
		baiter->Update(deltaTime);
	}
}

void BaiterControl::Draw()
{
	for (const auto& baiter : Baiters)
	{
		baiter->Draw();
	}
}

void BaiterControl::Activate()
{
	IsOn = true;
	SpawnTimer.Reset();
}

void BaiterControl::Deactivate()
{
	IsOn = false;
	IsDown = false;

	for (const auto& baiter : Baiters)
	{
		baiter->Enabled = false;

		for (auto& shot : baiter->Shots)
		{
			shot.Enabled = false;
		}
	}
}

void BaiterControl::Smartbomb(float xMin, float xMax)
{
	for (const auto& baiter : Baiters)
	{
		if (baiter->Enabled)
		{
			if (baiter->X() > xMin && baiter->X() < xMax)
			{
				if (baiter->Enabled)
				{
					Score->AddToScore(baiter->ScoreAmount);
					baiter->Hit();
				}
			}
		}
	}
}

void BaiterControl::NewWave()
{
	WaveTimer.Reset();
	Deactivate();
}

void BaiterControl::IsDownTime()
{
	IsDown = true;
	DownToTimer.Reset();
}

void BaiterControl::Spawn()
{
	size_t spawnNumber = Baiters.size();
	int baiterCount = 0;
	bool spawnNew = true;

	for (const auto& baiter : Baiters)
	{
		if (!baiter->Enabled)
		{
			spawnNumber = baiterCount;
			spawnNew = false;
			break;
		}

		baiterCount++;
	}

	if (spawnNew)
	{
		Baiters.push_back(DBG_NEW Baiter());
		Baiters[spawnNumber]->Initialize();
		Baiters[spawnNumber]->SetModel(BaiterModel, 10.0f);
		Baiters[spawnNumber]->SetShotModel(ShotModel);
		Baiters[spawnNumber]->SetRadarModel(RadarModel, 3.0f);
		Baiters[spawnNumber]->SetPlayer(ThePlayer);
		Baiters[spawnNumber]->SetExplosion(Explosion);
		Baiters[spawnNumber]->SetSounds(ShotSound, ExplosionSound);
		Baiters[spawnNumber]->SetScore(Score, 200);
		Baiters[spawnNumber]->BeginRun(TheCamera);
	}

	Baiters[spawnNumber]->Spawn({ ThePlayer->X(),  -(float)GetScreenHeight(), 0},
		-ThePlayer->Velocity.x);
}