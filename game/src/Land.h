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
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;
	Model3D* UIBackR = new Model3D();
	Model3D* UIBackL = new Model3D();
	Model3D* RadarHorzBottom = new Model3D();
	Model3D* RadarHorzTop = new Model3D();
	Model3D* RadarHorzL = new Model3D();
	Model3D* RadarHorzR = new Model3D();

	Vector2 UpdateRadar(float X, float Y);
};

