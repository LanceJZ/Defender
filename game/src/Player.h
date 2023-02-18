#pragma once
#include "raylib.h"
#include "Model3D.h"

class Player : public Model3D
{
public:
	Player();
	virtual ~Player();

	void SetCamera(Camera* camera);
	void SetFlameModel(Model model, Texture2D texture);
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
	float ForwardSpeed = 40;
	float MaxFowardV = 1000;
	float ForwardDrag = 15;
	Camera* TheCamera;
	Model3D Flame;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void CheckPlayfieldSide();
};

