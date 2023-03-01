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
		land->ModelScale = 50.0f;
		land->Position.y = (-GetScreenHeight() / 2.0f) + 160.0f;
		land->Position.x = ((-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i));
		land->Position.z = -40.0f;
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

	DrawLine3D({ (float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

	DrawLine3D({ -(float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{-(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

}