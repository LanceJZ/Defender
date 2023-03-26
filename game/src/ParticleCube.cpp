#include "ParticleCube.h"

ParticleCube::ParticleCube()
{
}

ParticleCube::~ParticleCube()
{
}

bool ParticleCube::Initialize()
{
	Model3D::Initialize();

	return false;
}

bool ParticleCube::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	return false;
}

void ParticleCube::Update(float deltaTime)
{
	if (Enabled)
	{
		Model3D::Update(deltaTime);

		LifeTimer.Update(deltaTime);

		if (LifeTimer.Elapsed())
		{
			Enabled = false;
		}
	}
}

void ParticleCube::Draw()
{
	Model3D::Draw();

}

void ParticleCube::Spawn(Vector3 position, float time)
{
	Enabled = true;
	Position = position;
	LifeTimer.Reset(time);
	Velocity = GetRandomVelocity(GetRandomFloat(10.0f, 50.0f));
}