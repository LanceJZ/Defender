#pragma once
#include "Model3D.h"
#include "PlayerShot.h"

class Player : public Model3D
{
public:
	PlayerShot* Shots[4];

	Player();
	virtual ~Player();

	bool Initialize();
	void SetCamera(Camera* camera);
	void SetFlameModel(Model model, Texture2D texture);
	void SetShotModels(Model model, Texture2D texture, Model tailModel, Texture2D tailTexture);
	void Load();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	bool FacingRight = true;
	float HorzSpeed = 30;
	float HorzMaxSpeed = 200;
	float HorzDrag = 2;
	float ForwardAcceleration = 40;
	float MaxFowardV = 1000;
	float ForwardDrag = 15;
	float AirDrag = 0.004;
	Camera* TheCamera;
	Model3D Flame;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Horzfriction();
	void ThrustOff();
	void Fire();
};

