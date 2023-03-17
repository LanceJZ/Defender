#include "Land.h"

Land::Land()
{
	for (int i = 0; i < 9; i++)
	{
		LandParts[i] = new Model3D();
	}

	for (int i = 0; i < 14; i++)
	{
		RadarLandParts[i] = new Model3D();
	}
}

Land::~Land()
{
}

void Land::SetUIBack(Model model)
{
	UIBackL->TheModel = model;
	UIBackR->TheModel = model;
}

void Land::SetUIHorz(Model model)
{
	RadarHorzL->TheModel = model;
	RadarHorzR->TheModel = model;
}

void Land::SetRadarTopBottom(Model model)
{
	RadarHorzBottom->TheModel = model;
	RadarHorzTop->TheModel = model;
}

void Land::SetStar(Model model)
{
	Star = model;
}

void Land::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool Land::Initialize()
{
	for (auto land : LandParts)
	{
		land->Initialize();
	}

	for (auto radar : RadarLandParts)
	{
		radar->Initialize();
	}

	for (int i = 0; i <= 66; i++)
	{
		AllTheStars.push_back(new Model3D());
	}

	UIBackL->Cull = false;
	UIBackR->Cull = false;
	RadarHorzBottom->Cull = false;
	RadarHorzL->Cull = false;
	RadarHorzR->Cull = false;
	RadarHorzTop->Cull = false;

	StarTimer->Set(1.0f);

	return false;
}

bool Land::BeginRun(Camera* camera)
{
	TheCamera = camera;
	int i = 0;

	for (auto land : LandParts)
	{
		land->ModelScale = 50.0f;
		land->Y((-GetScreenHeight() / 2.0f) + 160.0f);
		land->X((-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i));
		land->Z(-40.0f);
		i++;

		land->BeginRun(camera);
		land->ViewableArea.x = GetScreenWidth() * 1.5f;
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

		radar->BeginRun(camera);
	}

	UIBackL->ModelScale = 30;
	UIBackR->ModelScale = UIBackL->ModelScale;
	UIBackL->Y(GetScreenHeight() / 2.321f);
	UIBackR->Position = UIBackL->Position;
	UIBackR->Rotation = PI;
	UIBackR->RotationAxis.z = 1;
	UIBackL->BeginRun(camera);
	UIBackR->BeginRun(camera);

	RadarHorzBottom->ModelScale = 21.8f;
	RadarHorzTop->ModelScale = RadarHorzBottom->ModelScale;
	RadarHorzTop->RotationAxis = { 1.0f, 0, 0 };
	RadarHorzTop->Rotation = PI;
	RadarHorzL->ModelScale = RadarHorzBottom->ModelScale;
	RadarHorzR->ModelScale = RadarHorzBottom->ModelScale;
	RadarHorzTop->Y(GetScreenHeight() / 2.02f);
	RadarHorzBottom->Y(GetScreenHeight() / 2.79f);
	RadarHorzTop->BeginRun(camera);
	RadarHorzBottom->BeginRun(camera);
	RadarHorzL->Y(RadarHorzBottom->Y());
	RadarHorzR->Y(RadarHorzBottom->Y());
	RadarHorzL->BeginRun(camera);
	RadarHorzR->BeginRun(camera);

	CreateAllTheStars();

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

	UpdateAllTheStars(deltaTime);
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

	for (auto star : AllTheStars)
	{
		star->Draw();
	}

	UIBackL->Draw();
	UIBackR->Draw();
	RadarHorzBottom->Draw();
	RadarHorzTop->Draw();
	RadarHorzL->Draw();
	RadarHorzR->Draw();

	DrawLine3D({ (float)GetScreenWidth() * 3.5f, (float)GetScreenHeight() * 0.35f, 0},
		{(float)GetScreenWidth() * 3.5f, -(float)GetScreenHeight(), 0}, WHITE);

	DrawLine3D({ -(float)GetScreenWidth() * 3.5f, (float)GetScreenHeight() * 0.35f, 0},
		{-(float)GetScreenWidth() * 3.5f, -(float)GetScreenHeight(), 0}, WHITE);

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

void Land::CreateAllTheStars()
{
	for (auto star : AllTheStars)
	{
		star->X(GetRandomFloat((float)(-GetScreenWidth() * 3.5f), (float)(GetScreenWidth() * 3.5f)));
		star->Y(GetRandomFloat((float)(-GetScreenHeight() * 0.3f), (float)(GetScreenHeight() * 0.333f)));
		star->Z(-10);
		star->ModelColor = {(unsigned char)GetRandomValue(10, 200),
			(unsigned char)GetRandomValue(10, 200), (unsigned char)GetRandomValue(10, 200), 255 };
	}

	vector <Vector2> starLEdge;
	vector <Vector2> starREdge;
	vector <Color> starLColor;
	vector <Color> starRColor;

	for (auto star : AllTheStars)
	{

		if (star->X() > GetScreenWidth() * 2.5f)
		{
			starREdge.push_back({ star->X(), star->Y() });
			starRColor.push_back(star->ModelColor);
		}

		if (star->X() < -GetScreenWidth() * 2.5f)
		{
			starLEdge.push_back({ star->X(), star->Y() });
			starLColor.push_back(star->ModelColor);
		}
	}

	int iR = 0;

	for (auto star : starREdge)
	{
		AllTheStars.push_back(new Model3D());
		AllTheStars[AllTheStars.size() - 1]->X(star.x - (GetScreenWidth() * 7.0f));
		AllTheStars[AllTheStars.size() - 1]->Y(star.y);
		AllTheStars[AllTheStars.size() - 1]->ModelColor = starRColor[iR];
		iR++;
	}

	int iL = 0;

	for (auto star : starLEdge)
	{
		AllTheStars.push_back(new Model3D());
		AllTheStars[AllTheStars.size() - 1]->X(star.x + (GetScreenWidth() * 7.0f));
		AllTheStars[AllTheStars.size() - 1]->Y(star.y);
		AllTheStars[AllTheStars.size() - 1]->ModelColor = starLColor[iL];
		iL++;
	}

	for (auto star : AllTheStars)
	{
		star->Initialize();
		star->TheModel = Star;
		star->ModelScale = 6;
		star->BeginRun(TheCamera);
	}
}

void Land::UpdateAllTheStars(float deltaTime)
{
	StarTimer->Update(deltaTime);

	if (StarTimer->Elapsed())
	{
		StarTimer->Reset(GetRandomFloat(0.1f, 0.75f));

		for (auto star : AllTheStars)
		{
			star->Enabled = true;
		}

		AllTheStars[(size_t)GetRandomValue(0, (int)AllTheStars.size() - 1)]->Enabled = false;
	}

	for (auto star : AllTheStars)
	{
		//star->Update(deltaTime);
	}
}
