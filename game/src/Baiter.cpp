#include "Baiter.h"

Baiter::Baiter()
{
}

Baiter::~Baiter()
{
}

bool Baiter::Initialize()
{
	Model3D::Initialize();

	return false;
}

bool Baiter::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	return false;
}

void Baiter::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Baiter::Draw()
{
	Model3D::Draw();

}
