#include "Bomb.h"

Bomb::Bomb()
{

}

Bomb::~Bomb()
{
}

void Bomb::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);
}

bool Bomb::Initialize()
{
	Model3D::Initialize();

	return false;
}

bool Bomb::BeginRun()
{

	return false;
}

void Bomb::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Bomb::Draw()
{
	Model3D::Draw();

}