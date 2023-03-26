#pragma once
#include "Model3D.h"
#include "PlayerShot.h"
#include "ExplosionControl.h"

class Player : public Model3D
{
public:
	PlayerShot Shots[(int)4];

	Player();
	virtual ~Player();

	bool Initialize();
	void SetModel(Model model);
	void SetFlameModel(Model model);
	void SetShotModel(Model model);
	void SetTailModel(Model model);
	void SetRadarModel(Model model);
	void SetSounds(Sound shot, Sound explode, Sound thrust);
	void SetExplosion(ExplosionControl* explosion);
	bool BeginRun(Camera* camera);

	void Input();
	void Update(float deltaTime);
	void Draw();

	void Reset();
	void Hit();

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
	Sound ShotSound = { 0 };
	Sound ExplodeSound = { 0 };
	Sound ThrustSound = { 0 };
	Model ShotModel;
	Model ShotTrailModel;
	Model RadarModel;
	Model3D Flame;
	Model3D Radar;
	Camera* TheCamera = nullptr;
	ExplosionControl* Explosion = nullptr;

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

