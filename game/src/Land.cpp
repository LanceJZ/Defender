#include "Land.h"

Land::Land()
{
	for (int i = 0; i < 9; i++)
	{
		LandParts[i] = new Model3D();
		Radar[i] = new Model3D();
	}

	for (auto land : LandParts)
	{
		land->Initialize();
	}

	for (auto radar : Radar)
	{
		radar->Initialize();
	}

	UIBackL = new Model3D();
	UIBackR = new Model3D();
	RadarHorzBottom = new Model3D;
	RadarHorzTop = new Model3D;
	RadarHorzL = new Model3D;
	RadarHorzR = new Model3D;
}

Land::~Land()
{
}

void Land::SetUIBack(Model model, Texture2D texture)
{
	UIBackL->LoadModel(model, texture);
	UIBackR->LoadModel(model, texture);
}

void Land::SetRadarHorz(Model model, Texture2D texture)
{
	RadarHorzBottom->LoadModel(model, texture);
	RadarHorzTop->LoadModel(model, texture);
	RadarHorzL->LoadModel(model, texture);
	RadarHorzR->LoadModel(model, texture);
}

void Land::SetCamera(Camera* camera)
{
	TheCamera = camera;
}

bool Land::BeginRun()
{
	int i = 0;

	for (auto land : LandParts)
	{
		land->ModelScale = 50.0f;
		land->Y((-GetScreenHeight() / 2.0f) + 160.0f);
		land->X((-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i));
		land->Z(-40.0f);
		i++;
	}

	LandParts[7]->TheModel = LandParts[0]->TheModel;
	LandParts[8]->TheModel = LandParts[6]->TheModel;

	LandParts[7]->Position.x = GetScreenWidth() * 4.0f;
	LandParts[8]->Position.x = -GetScreenWidth() * 4.0f;

	i = 0;

	for (auto radar : Radar)
	{
		radar->TheModel = LandParts[i]->TheModel;
		radar->ModelScale = 5.0f;
		radar->Y(GetScreenHeight() / 3.0f);
		radar->Z(-10.0f);
		i++;
	}

	UIBackL->ModelScale = 30;
	UIBackR->ModelScale = UIBackL->ModelScale;
	UIBackL->Y(GetScreenHeight() / 2.321f);
	UIBackR->Position = UIBackL->Position;

	RadarHorzBottom->ModelScale = 21.8f;
	RadarHorzTop->ModelScale = RadarHorzBottom->ModelScale;
	RadarHorzL->ModelScale = RadarHorzBottom->ModelScale;
	RadarHorzR->ModelScale = RadarHorzBottom->ModelScale;
	RadarHorzTop->Y(GetScreenHeight() / 2.02f);
	RadarHorzBottom->Y(GetScreenHeight() / 2.79f);
	RadarHorzL->Y(RadarHorzBottom->Y());
	RadarHorzR->Y(RadarHorzBottom->Y());

	return false;
}

void Land::Input()
{

}

void Land::Update(float deltaTime)
{
	int sWidth = GetScreenWidth();

	UIBackL->X(TheCamera->position.x - (sWidth / 2.790f));
	UIBackR->X(TheCamera->position.x + (sWidth / 2.790f));
	RadarHorzBottom->X(TheCamera->position.x);
	RadarHorzTop->X(RadarHorzBottom->X());
	RadarHorzL->X(TheCamera->position.x - (sWidth / 2.3f));
	RadarHorzR->X(TheCamera->position.x +(sWidth / 2.3f));

	//for (int i = 0; i < 7; i++)
	//{
	//	Radar[i]->Position.x = TheCamera->position.x + (-sWidth / 4.0f) + (i * sWidth / 10) -20.0f;
	//}

	//Radar[7]->Position.x = TheCamera->position.x + (sWidth / 4.0f) + (sWidth / 10);
	//Radar[8]->Position.x = TheCamera->position.x + (-sWidth / 4.0f) - (sWidth / 10);
}

void Land::Draw()
{
	for (auto land : LandParts)
	{
		land->Draw();
	}

	UIBackL->Draw();
	UIBackR->Draw();
	RadarHorzBottom->Draw();
	RadarHorzTop->Draw();
	RadarHorzL->Draw();
	RadarHorzR->Draw();

	//for (auto radar : Radar)
	//{
	//	radar->Draw();
	//}
	//for (int i = 0; i < 7; i++)
	//{
	//	Radar[i]->Draw();
	//}

	DrawLine3D({ (float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

	DrawLine3D({ -(float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{-(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

}