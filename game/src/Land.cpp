#include "Land.h"

Land::Land()
{
}

Land::~Land()
{
	for (int i = 0; i < 7; i++)
	{
		LandParts[i].Unload();
		RadarLandParts[i].Unload();
	}

	UIBackR.Unload();
	RadarHorzBottom.Unload();
	RadarHorzL.Unload();
	UnloadModel(StarModel);

	TheCamera = nullptr;
	ThePlayer = nullptr;
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
	UIBackL.SetModel(model, 30.0f);
	UIBackR.SetModel(model, 30.0f);
}

void Land::SetUIHorz(Model model)
{
	RadarHorzL.SetModel(model, 21.8f);
	RadarHorzR.SetModel(model, 21.8f);
}

void Land::SetRadarTopBottom(Model model)
{
	RadarHorzBottom.SetModel(model, 21.8f);
	RadarHorzTop.SetModel(model, 21.8f);
}

void Land::SetStar(Model model)
{
	StarModel = model;
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
		land.Y((-GetScreenHeight() / 2.0f) + 160.0f);
		land.X((-GetScreenWidth() * 3.0f) + (GetScreenWidth() * i));
		land.Z(-40.0f);
		i++;

		land.BeginRun(camera);
		land.ViewableArea.x = GetScreenWidth() * 1.5f;
	}

	LandParts[7].SetModel(LandParts[0].GetModel(), 50.0f);
	LandParts[8].SetModel(LandParts[6].GetModel(), 50.0f);

	for (int i = 7; i < 14; i++)
	{
		RadarLandParts[i].SetModel(RadarLandParts[i - 7].GetModel(), 3.18f);
	}

	LandParts[7].Position.x = GetScreenWidth() * 4.0f;
	LandParts[8].Position.x = -GetScreenWidth() * 4.0f;

	i = 0;

	for (auto &radar : RadarLandParts)
	{
		radar.Y(UpdateRadar(0, LandParts[0].Y()).y);
		radar.Z(-10.0f);
		i++;

		radar.BeginRun(camera);
	}

	UIBackL.Y(GetScreenHeight() / 2.321f);
	UIBackR.Position = UIBackL.Position;
	UIBackR.Rotation = PI;
	UIBackR.RotationAxis.z = 1;
	UIBackL.BeginRun(camera);
	UIBackR.BeginRun(camera);

	RadarHorzTop.RotationAxis = { 1.0f, 0, 0 };
	RadarHorzTop.Rotation = PI;
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
	if (!AllDead)
	{
		for (auto &land : LandParts)
		{
			land.Draw();
		}

		for (auto &radar : RadarLandParts)
		{
			radar.Draw();
		}
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

#ifdef _DEBUG
	DrawLine3D({ (float)GetScreenWidth() * 3.5f, (float)GetScreenHeight() * 0.35f, 0},
		{(float)GetScreenWidth() * 3.5f, -(float)GetScreenHeight(), 0}, WHITE);

	DrawLine3D({ -(float)GetScreenWidth() * 3.5f, (float)GetScreenHeight() * 0.35f, 0},
		{-(float)GetScreenWidth() * 3.5f, -(float)GetScreenHeight(), 0}, WHITE);
#endif
}

void Land::AllThePersonManDead()
{
	AllDead = true;
	CreateAllTheStars();
}

void Land::NewLevel()
{
	CreateAllTheStars();
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
		AllTheStars[i].X(GetRandomFloat((float)(-GetScreenWidth() * 3.5f),
			(float)(GetScreenWidth() * 3.5f)));

		if (AllDead)
		{
			AllTheStars[i].Y(GetRandomFloat((float)(-GetScreenHeight()),
				(float)(GetScreenHeight() * 0.333f)));
		}
		else
		{
			AllTheStars[i].Y(GetRandomFloat((float)(-GetScreenHeight() * 0.3f),
				(float)(GetScreenHeight() * 0.333f)));
		}

		AllTheStars[i].Z(-10);
		AllTheStars[i].ModelColor = {(unsigned char)GetRandomValue(10, 200),
			(unsigned char)GetRandomValue(10, 200), (unsigned char)GetRandomValue(10, 200), 255 };
	}

	std::vector <Vector2> starLEdge;
	std::vector <Vector2> starREdge;
	std::vector <Color> starLColor;
	std::vector <Color> starRColor;

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

	int iL = (int)starREdge.size() + iR;

	for (int i = 0; i < starLEdge.size(); i++)
	{
		AllTheStars[iL + i].X(starLEdge[i].x + (GetScreenWidth() * 7.0f));
		AllTheStars[iL + i].Y(starLEdge[i].y);
		AllTheStars[iL + i].ModelColor = starLColor[i];
	}

	NumberOfStars = mainStars + (int)starLEdge.size() + (int)starREdge.size();

	for (int i = NumberOfStars; i < mainStars; i++)
	{
		AllTheStars[i].Enabled = false;
	}

	for (auto &star : AllTheStars)
	{
		star.Initialize();
		star.SetModel(StarModel, 6.5f);
		star.BeginRun(TheCamera);
		star.RotationAxis = { 1, 1, 1 };
		star.RotationVelocity = 16.66f;
	}
}

void Land::UpdateAllTheStars(float deltaTime)
{
	StarTimer.Update(deltaTime);

	for (auto &star : AllTheStars)
	{
		star.Update(deltaTime);
	}

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
