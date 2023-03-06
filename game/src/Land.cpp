#include "Land.h"

Land::Land()
{
	ThePlayer = nullptr;
	TheCamera = nullptr;

	for (int i = 0; i < 9; i++)
	{
		LandParts[i] = new Model3D();
	}

	for (int i = 0; i < 14; i++)
	{
		RadarLandParts[i] = new Model3D();
	}

	for (auto land : LandParts)
	{
		land->Initialize();
	}

	for (auto radar : RadarLandParts)
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

void Land::SetPlayer(Player* player)
{
	ThePlayer = player;
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

	for (int i = 7; i < 14; i++)
	{
		RadarLandParts[i]->TheModel = RadarLandParts[i - 7]->TheModel;
	}

	LandParts[7]->Position.x = GetScreenWidth() * 4.0f;
	LandParts[8]->Position.x = -GetScreenWidth() * 4.0f;

	i = 0;

	for (auto radar : RadarLandParts)
	{
		radar->ModelScale = 3.18f;
		radar->Y(UpdateRadar(0, LandParts[0]->Y()).y);
		radar->Z(-10.0f);
		i++;
	}

	UIBackL->ModelScale = 30;
	UIBackR->ModelScale = UIBackL->ModelScale;
	UIBackL->Y(GetScreenHeight() / 2.321f);
	UIBackR->Position = UIBackL->Position;
	UIBackR->Rotation = PI;
	UIBackR->RotationAxis.z = 1;

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

void Land::Update(float deltaTime)
{
	int sWidth = GetScreenWidth();

	UIBackL->X(TheCamera->position.x - (sWidth / 2.790f));
	UIBackR->X(TheCamera->position.x + (sWidth / 2.790f));
	RadarHorzBottom->X(TheCamera->position.x);
	RadarHorzTop->X(RadarHorzBottom->X());
	RadarHorzL->X(TheCamera->position.x - (sWidth / 2.3f));
	RadarHorzR->X(TheCamera->position.x + (sWidth / 2.3f));

	for (int i = 0; i < 7; i++)
	{
		RadarLandParts[i]->X(UpdateRadar(LandParts[i]->X(), 0).x);
	}

	for (int i = 7; i < 11; i++)
	{
		RadarLandParts[i]->X(UpdateRadar(LandParts[i - 7]->X() + (GetScreenWidth() * 7), 0).x);
	}

	for (int i = 11; i < 14; i++)
	{
		RadarLandParts[i]->X(UpdateRadar(LandParts[i - 7]->X() - (GetScreenWidth() * 7), 0).x);
	}

	for (auto radar : RadarLandParts)
	{
		radar->Enabled = LandParts[0]->Enabled;
	}
}

void Land::Draw()
{
	for (auto land : LandParts)
	{
		land->Draw();
	}

	for (auto radar : RadarLandParts)
	{
		radar->Draw();
	}

	UIBackL->Draw();
	UIBackR->Draw();
	RadarHorzBottom->Draw();
	RadarHorzTop->Draw();
	RadarHorzL->Draw();
	RadarHorzR->Draw();

	DrawLine3D({ (float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

	DrawLine3D({ -(float)GetScreenWidth() * 3.5f, (float)GetScreenHeight(), 0},
		{-(float)GetScreenWidth() * 3.5f, (float) - GetScreenHeight(), 0}, WHITE);

}

Vector2 Land::UpdateRadar(float X, float Y)
{
	float comp = 0.062f;
	float ww = 7.0f;
	float swww = (GetScreenWidth() * ww);
	float swcalc = (swww * comp);
	float swwwcalc = (swww * 2) * comp;

	X = (TheCamera->position.x + (-ThePlayer->X() * comp) + (X * comp));

	if (X > TheCamera->position.x + swcalc)
	{
		X = (X - swwwcalc);
	}
	else if (X < TheCamera->position.x - swcalc)
	{
		X = (X + swwwcalc);
	}

	Y = ((Y * 0.148f) + (GetScreenHeight() * 0.4376f));

	return { X, Y };
}
