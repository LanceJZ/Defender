#pragma once
#include "Model3D.h"
#include "PlayerShot.h"

class Player : public Model3D
{
public:
	PlayerShot* Shots[(int)4];

	Player();
	virtual ~Player();

	bool Initialize();
	void SetModel(Model model);
	void SetFlameModel(Model model);
	void SetShotModel(Model model);
	void SetTailModel(Model model);
	void SetRadarModel(Model model);
	bool BeginRun(Camera* camera);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void NewWaveReset();

private:
	bool FacingRight = true;
	bool ChangedFacing = false;
	bool RotateFacing = false;
	float moveToOffset = 1000;
	float HorzSpeed = 30.0f;
	float HorzMaxSpeed = 200.0f;
	float HorzDrag = 2.0f;
	float ForwardAcceleration = 40.0f;
	float MaxFowardV = 1000.0f;
	float ForwardDrag = 20.0f;
	float AirDrag = 0.004f;
	Camera* TheCamera = nullptr;
	Model3D Flame;
	Model3D Radar;

	void CameraMovement();
	void RadarMovement();
	void RotateShipFacing();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Reverse();
	void Horzfriction();
	void Thrust();
	void ThrustOff();
	void Fire();
	void SmartBomb();
	void Hyperspace();
};

