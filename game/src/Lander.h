#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "Timer.h"
#include "Player.h"
#include "EnemyRadar.h"

class Lander : public Model3D
{
public:


	Lander();
	virtual ~Lander();

	EnemyShot* Shots[4];

	void SetModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	void SetRadarModel(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	bool PickUpMode = false;
	bool GoingDownForPickupMode = false;
	bool SeekMode = false;
	bool GoToGroundMode = true;
	float GroundHoverY = 0;
	Timer* ShotTimer;
	Model3D MirrorR;
	Model3D MirrorL;
	EnemyRadar Radar;
	Player* ThePlayer;
	Camera* TheCamera;

	void FireShot();
	void FireShots();
	float AimedShot();
	void MirrorUpdate();
};

