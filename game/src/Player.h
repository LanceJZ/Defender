#pragma once
#include "Model3D.h"
#include "PlayerShot.h"
#include "ExplosionControl.h"

class Player : public Model3D
{
public:
	Player();
	virtual ~Player();

	bool GameOver = false;
	bool SmartBombFired = false;
	PlayerShot Shots[(int)4];
	Entity BackCollusion;
	Entity FrontCollusion;

	bool Initialize();
	void SetModel(Model model);
	void SetFlameModel(Model model);
	void SetShotModel(Model model);
	void SetTailModel(Model model);
	void SetRadarModel(Model model);
	void SetSmartbombModel(Model model);
	void SetSounds(Sound shot, Sound explode, Sound thrust, Sound bomb);
	void SetExplosion(ExplosionControl* explosion);
	bool BeginRun(Camera* camera);

	void Input();
	void Update(float deltaTime);
	void Draw();

	void Reset();
	void NewGame();
	void NewWave();
	void Hit();
	void Bonus();

private:
	bool FacingRight = true;
	bool ChangedFacing = false;
	bool RotateFacing = false;
	int Lives = 0;
	int SmartBombs = 0;
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
	Sound SmartbombSound = { 0 };
	Model ShotModel = { 0 };
	Model ShotTrailModel = { 0 };
	Model RadarModel = { 0 };
	Model SmartbombModel = { 0 };
	Model3D Flame;
	Model3D Radar;
	Camera* TheCamera = nullptr;
	ExplosionControl* Explosion = nullptr;

	std::vector<Model3D*> LivesShips;
	std::vector<Model3D*> SmartbombIcons;

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
	void LivesDisplay();
	void LivesDisplayUpdate();
	void SmartbombsDisplay();
	void SmartbombsDisplayUpdate();
};

