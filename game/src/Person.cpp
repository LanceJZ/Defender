#include "Person.h"

Person::Person()
{
	ThePlayer = nullptr;
	Enabled = false;
}

Person::~Person()
{
}

void Person::SetModel(Model model, Texture2D texture)
{
	Model3D::LoadModel(model, texture);

}

void Person::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool Person::Initialize()
{
	Model3D::Initialize();

	ModelScale = 5;

	return false;
}

bool Person::BeginRun()
{
	MirrorR = TheModel;
	MirrorL = TheModel;

	return false;
}

void Person::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Person::Draw()
{
	Model3D::Draw();

	float mirror = 7.0f;
	DrawModel(MirrorR, { X() + GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
	DrawModel(MirrorL, { X() - GetScreenWidth() * mirror, Y(), 0}, ModelScale, ModelColor);
}

void Person::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;
}
