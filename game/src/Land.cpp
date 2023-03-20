#include "Land.h"

Land::Land()
{
}

Land::~Land()
{
}

bool Land::Initialize()
{
	for (auto &land : LandParts)
	{
		land.Initialize();
	}

	for (auto &radar : RadarLandParts)
	{
		radar.Initialize();
	}

	for (auto& star : AllTheStars)
	{
		star.Initialize();
	}

	UIBackL.Cull = false;
	UIBackR.Cull = false;
	RadarHorzBottom.Cull = false;
	RadarHorzL.Cull = false;
	RadarHorzR.Cull = false;
	RadarHorzTop.Cull = false;

	StarTimer.Set(1.0f);

	return false;
}

void Land::SetUIBack(Model model)
{
	UIBackL.SetModel(model);
	UIBackR.SetModel(model);
}

void Land::SetUIHorz(Model model)
{
	RadarHorzL.SetModel(model);
	RadarHorzR.SetModel(model);
}

void Land::SetRadarTopBottom(Model model)
{
	RadarHorzBottom.SetModel(model);
	RadarHorzTop.SetModel(model);
}

void Land::SetStar(Model model)
{
	Star = model;
}

void Land::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool Land::BeginRun(Camera* camera)
{
	TheCamera = camera;
	int i = 0;

	for (auto &land : LandParts)
	{
		land.ModelScale = 50.0f;
		land.Y((-GetScreenHeight() / 2.0f) + 160.0f);
		land.X((-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i));
		land.Z(-40.0f);
		i++;

		land.BeginRun(camera);
		land.ViewableArea.x = GetScreenWidth() * 1.5f;
	}

	LandParts[7].SetModel(LandParts[0].GetModel());
	LandParts[8].SetModel(LandParts[6].GetModel());

	for (int i = 7; i < 14; i++)
	{
		RadarLandParts[i].SetModel(RadarLandParts[i - 7].GetModel());
	}

	LandParts[7].Position.x = GetScreenWidth() * 4.0f;
	LandParts[8].Position.x = -GetScreenWidth() * 4.0f;

	i = 0;

	for (auto &radar : RadarLandParts)
	{
		radar.ModelScale = 3.18f;
		radar.Y(UpdateRadar(0, LandParts[0].Y()).y);
		radar.Z(-10.0f);
		i++;

		radar.BeginRun(camera);
	}

	UIBackL.ModelScale = 30;
	UIBackR.ModelScale = UIBackL.ModelScale;
	UIBackL.Y(GetScreenHeight() / 2.321f);
	UIBackR.Position = UIBackL.Position;
	UIBackR.Rotation = PI;
	UIBackR.RotationAxis.z = 1;
	UIBackL.BeginRun(camera);
	UIBackR.BeginRun(camera);

	RadarHorzBottom.ModelScale = 21.8f;
	RadarHorzTop.ModelScale = RadarHorzBottom.ModelScale;
	RadarHorzTop.RotationAxis = { 1.0f, 0, 0 };
	RadarHorzTop.Rotation = PI;
	RadarHorzL.ModelScale = RadarHorzBottom.ModelScale;
	RadarHorzR.ModelScale = RadarHorzBottom.ModelScale;
	RadarHorzTop.Y(GetScreenHeight() / 2.02f);
	RadarHorzBottom.Y(GetScreenHeight() / 2.79f);
	RadarHorzTop.BeginRun(camera);
	RadarHorzBottom.BeginRun(camera);
	RadarHorzL.Y(RadarHorzBottom.Y());
	RadarHorzR.Y(RadarHorzBottom.Y());
	RadarHorzL.BeginRun(camera);
	RadarHorzR.BeginRun(camera);

	CreateAllTheStars();

	return false;
}

void Land::Update(float deltaTime)
{
	int sWidth = GetScreenWidth();

	UIBackL.X(TheCamera->position.x - (sWidth / 2.790f));
	UIBackR.X(TheCamera->position.x + (sWidth / 2.790f));
	RadarHorzBottom.X(TheCamera->position.x);
	RadarHorzTop.X(RadarHorzBottom.X());
	RadarHorzL.X(TheCamera->position.x - (sWidth / 2.3f));
	RadarHorzR.X(TheCamera->position.x + (sWidth / 2.3f));

	for (int i = 0; i < 7; i++)
	{
		RadarLandParts[i].X(UpdateRadar(LandParts[i].X(), 0).x);
	}

	for (int i = 7; i < 11; i++)
	{
		RadarLandParts[i].X(UpdateRadar(LandParts[i - 7].X() + (GetScreenWidth() * 7), 0).x);
	}

	for (int i = 11; i < 14; i++)
	{
		RadarLandParts[i].X(UpdateRadar(LandParts[i - 7].X() - (GetScreenWidth() * 7), 0).x);
	}

	for (auto &radar : RadarLandParts)
	{
		radar.Enabled = LandParts[0].Enabled;
	}

	UpdateAllTheStars(deltaTime);
}

void Land::Draw()
{
	for (auto &land : LandParts)
	{
		land.Draw();
	}

	for (auto &radar : RadarLandParts)
	{
		radar.Draw();
	}

	for (auto &star : AllTheStars)
	{
		star.Draw();
	}

	UIBackL.Draw();
	UIBackR.Draw();
	RadarHorzBottom.Draw();
	RadarHorzTop.Draw();
	RadarHorzL.Draw();
	RadarHorzR.Draw();

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
	int mainStars = 66;

	for (int i = 0; i < mainStars; i++)
	{
		AllTheStars[i].X(GetRandomFloat((float)(-GetScreenWidth() * 3.5f), (float)(GetScreenWidth() * 3.5f)));
		AllTheStars[i].Y(GetRandomFloat((float)(-GetScreenHeight() * 0.3f), (float)(GetScreenHeight() * 0.333f)));
		AllTheStars[i].Z(-10);
		AllTheStars[i].ModelColor = {(unsigned char)GetRandomValue(10, 200),
			(unsigned char)GetRandomValue(10, 200), (unsigned char)GetRandomValue(10, 200), 255 };
	}

	vector <Vector2> starLEdge;
	vector <Vector2> starREdge;
	vector <Color> starLColor;
	vector <Color> starRColor;

	for (int i = 0; i < mainStars; i++)
	{
		if (AllTheStars[i].X() > GetScreenWidth() * 2.5f)
		{
			starREdge.push_back({ AllTheStars[i].X(), AllTheStars[i].Y()});
			starRColor.push_back(AllTheStars[i].ModelColor);
		}

		if (AllTheStars[i].X() < -GetScreenWidth() * 2.5f)
		{
			starLEdge.push_back({ AllTheStars[i].X(), AllTheStars[i].Y()});
			starLColor.push_back(AllTheStars[i].ModelColor);
		}
	}

	int iR = mainStars;

	for (int i = 0; i < starREdge.size(); i++)
	{
		AllTheStars[iR + i].X(starREdge[i].x - (GetScreenWidth() * 7.0f));
		AllTheStars[iR + i].Y(starREdge[i].y);
		AllTheStars[iR + i].ModelColor = starRColor[i];
	}

	int iL = starREdge.size() + iR;

	for (int i = 0; i < starLEdge.size(); i++)
	{
		AllTheStars[iL + i].X(starLEdge[i].x + (GetScreenWidth() * 7.0f));
		AllTheStars[iL + i].Y(starLEdge[i].y);
		AllTheStars[iL + i].ModelColor = starLColor[i];
	}

	NumberOfStars = mainStars + starLEdge.size() + starREdge.size();

	for (int i = NumberOfStars; i < mainStars; i++)
	{
		AllTheStars[i].Enabled = false;
	}

	for (auto &star : AllTheStars)
	{
		star.Initialize();
		star.SetModel(Star);
		star.ModelScale = 6;
		star.BeginRun(TheCamera);
	}
}

void Land::UpdateAllTheStars(float deltaTime)
{
	StarTimer.Update(deltaTime);

	if (StarTimer.Elapsed())
	{
		StarTimer.Reset(GetRandomFloat(0.25f, 0.75f));

		for (int i = 0; i < 66; i++)
		{
			AllTheStars[i].Enabled = true;
		}

		AllTheStars[(size_t)GetRandomValue(0, 65)].Enabled = false;
	}
}
