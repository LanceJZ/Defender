#pragma once
#include "raylib.h"
#include "Model3D.h"

class Land
{
public:
	Model3D* LandParts[9];

	Land();
	virtual ~Land();

	void SetUIBack(Model model, Texture2D texture);
	void SetRadarHorz(Model model, Texture2D texture);
	void SetCamera(Camera* camera);
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Camera* TheCamera;
	Model3D* Radar[9];
	Model3D* UIBackR;
	Model3D* UIBackL;
	Model3D* RadarHorzBottom;
	Model3D* RadarHorzTop;
	Model3D* RadarHorzL;
	Model3D* RadarHorzR;
};

