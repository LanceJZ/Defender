#pragma once
#include "raylib.h"
#include "Common.h"
#include "Model3D.h"
#include "Player.h"
#include "Timer.h"

class Land : Common
{
public:
	Model3D* LandParts[9];
	Model3D* RadarLandParts[14];

	Land();
	virtual ~Land();

	void SetUIBack(Model model, Texture2D texture);
	void SetRadarHorz(Model model, Texture2D texture);
	void SetStar(Model model, Texture2D texture);
	void SetCamera(Camera* camera);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model Star = { 0 };
	Texture2D StarTexture = { 0 };
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;
	Timer* StarTimer = new Timer();
	Model3D* UIBackR = new Model3D();
	Model3D* UIBackL = new Model3D();
	Model3D* RadarHorzBottom = new Model3D();
	Model3D* RadarHorzTop = new Model3D();
	Model3D* RadarHorzL = new Model3D();
	Model3D* RadarHorzR = new Model3D();
	vector <Model3D*> AllTheStars;

	Vector2 UpdateRadar(float X, float Y);
	void CreateAllTheStars();
	void UpdateAllTheStars(float deltaTime);
};

