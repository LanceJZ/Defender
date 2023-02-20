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
	void SetCamera(Camera* camera);
	void SetFlameModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	void SetTailModel(Model model, Texture2D texture);
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	bool FacingRight = true;
	float HorzSpeed = 30.0f;
	float HorzMaxSpeed = 200.0f;
	float HorzDrag = 2.0f;
	float ForwardAcceleration = 40.0f;
	float MaxFowardV = 1000.0f;
	float ForwardDrag = 15.0f;
	float AirDrag = 0.004f;
	Camera* TheCamera;
	Model3D Flame;

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

