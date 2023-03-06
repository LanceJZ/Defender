#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Player.h"

class Land
{
public:
	Model3D* LandParts[9];
	Model3D* RadarLandParts[14];

	Land();
	virtual ~Land();

	void SetUIBack(Model model, Texture2D texture);
	void SetRadarHorz(Model model, Texture2D texture);
	void SetCamera(Camera* camera);
	void SetPlayer(Player* player);
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Camera* TheCamera;
	Player* ThePlayer;
	Model3D* UIBackR;
	Model3D* UIBackL;
	Model3D* RadarHorzBottom;
	Model3D* RadarHorzTop;
	Model3D* RadarHorzL;
	Model3D* RadarHorzR;

	Vector2 UpdateRadar(float X, float Y);
};

