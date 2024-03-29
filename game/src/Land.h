#pragma once
#include "raylib.h"
#include "Common.h"
#include "Model3D.h"
#include "Player.h"
#include "Timer.h"

class Land : Common
{
public:
	bool AllDead = false;
	Model3D LandParts[9];
	Model3D RadarLandParts[14];

	Land();
	virtual ~Land();

	bool Initialize();
	void SetUIBack(Model model);
	void SetUIHorz(Model model);
	void SetRadarTopBottom(Model model);
	void SetStar(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void AllThePersonManDead();
	void NewLevel();

private:
	int NumberOfStars = 0;
	Model StarModel = { 0 };
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;
	Timer StarTimer;
	Model3D UIBackR;
	Model3D UIBackL;
	Model3D RadarHorzBottom;
	Model3D RadarHorzTop;
	Model3D RadarHorzL;
	Model3D RadarHorzR;
	Model3D AllTheStars[100];

	Vector2 UpdateRadar(float X, float Y);
	void CreateAllTheStars();
	void UpdateAllTheStars(float deltaTime);
};

