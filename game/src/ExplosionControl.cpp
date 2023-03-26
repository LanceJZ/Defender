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
	for (int i = 0; i < count; i++)
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

		Particles[cubeSpawnNumber]->Spawn(position, time);
	}
}