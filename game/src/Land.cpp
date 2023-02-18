#include "Land.h"

Land::Land()
{
	for (int i = 0; i < 9; i++)
	{
		LandParts[i] = new Model3D();
	}

	for (auto land : LandParts)
	{
		land->Initialize();
	}
}

Land::~Land()
{
}

void Land::Load()
{

}

bool Land::BeginRun()
{
	int i = 0;

	for (auto land : LandParts)
	{
		land->ModelScale = 5.0f;
		land->Position.y = (-GetScreenHeight() / 2) + 160;
		land->Position.x = ((-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i));
		i++;
	}

	LandParts[7]->TheModel = LandParts[0]->TheModel;
	LandParts[8]->TheModel = LandParts[6]->TheModel;

	LandParts[7]->Position.x = GetScreenWidth() * 4.0f;
	LandParts[8]->Position.x = -GetScreenWidth() * 4.0f;

	return false;
}

void Land::Input()
{

}

void Land::Update(float deltaTime)
{
	for (auto land : LandParts)
	{
		land->Update(deltaTime);
	}
}

void Land::Draw()
{
	for (auto land : LandParts)
	{
		land->Draw();
	}
}