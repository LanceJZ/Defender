#include "ExplosionControl.h"

ExplosionControl::ExplosionControl()
{
}

ExplosionControl::~ExplosionControl()
{
	UnloadModel(CubeModel);
	TheCamera = nullptr;
}

bool ExplosionControl::Initialize()
{
	Xmult = GetScreenWidth() * 2.75f;
	MirrorMult = GetScreenWidth() * 7.0f;

	return false;
}

void ExplosionControl::SetCubeModel(Model model)
{
	CubeModel = model;
}

bool ExplosionControl::BeginRun(Camera* camera)
{
	TheCamera = camera;
	return false;
}

void ExplosionControl::Update(float deltaTime)
{
	for (auto cube : Particles)
	{
		cube->Update(deltaTime);
	}
}

void ExplosionControl::Draw()
{
	for (auto cube : Particles)
	{
		cube->Draw();
	}
}

void ExplosionControl::Spawn(Vector3 position, int count, float time)
{
	std::vector<int> spawnedNumbers;

	for (int i = 0; i < count; i++)
	{
		int spawnPoolNumber = SpawnPool();

		Particles[spawnPoolNumber]->Spawn(position, time);

		spawnedNumbers.push_back(spawnPoolNumber);
	}

	for (int i = 0; i < count; i++)
	{
		if (position.x > Xmult)
		{
			int spawnPoolNumberL = SpawnPool();
			Vector3 lPosition = { Particles[spawnedNumbers[i]]->Position.x - MirrorMult,
				position.y, 0};
			Particles[spawnPoolNumberL]->Spawn(lPosition, time);
			Particles[spawnPoolNumberL]->Velocity = Particles[i]->Velocity;
		}
		else if (position.x < -Xmult)
		{
			int spawnPoolNumberR = SpawnPool();
			Vector3 rPosition = { Particles[spawnedNumbers[i]]->Position.x + MirrorMult,
				position.y, 0};
			Particles[spawnPoolNumberR]->Spawn(rPosition, time);
			Particles[spawnPoolNumberR]->Velocity = Particles[i]->Velocity;
		}
	}
}

int ExplosionControl::SpawnPool()
{
		bool spawnNew = true;
		int cubeSpawnNumber = (int)Particles.size();
		int cubeNumber = 0;

		for (auto cube : Particles)
		{
			if (!cube->Enabled)
			{
				spawnNew = false;
				cubeSpawnNumber = cubeNumber;
				break;
			}

			cubeNumber++;
		}

		if (spawnNew)
		{
			Particles.push_back(new ParticleCube());
			Particles[cubeSpawnNumber]->Initialize();
			Particles[cubeSpawnNumber]->SetModel(CubeModel, 10);
			Particles[cubeSpawnNumber]->BeginRun(TheCamera);
		}

	return cubeSpawnNumber;
}
