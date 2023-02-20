#include "Lander.h"

Lander::Lander()
{
}

Lander::~Lander()
{
}

void Lander::SetShotModel(Model model, Texture2D texture)
{
	Shot.LoadModel(model, texture);
}

bool Lander::Initialize()
{
	Model3D::Initialize();

	ModelScale = 14;

	return false;
}

bool Lander::BeginRun()
{

	return false;
}

void Lander::Input()
{

}

void Lander::Update(float deltaTime)
{
	Model3D::Update(deltaTime);


}

void Lander::Draw()
{
	Model3D::Draw();


}