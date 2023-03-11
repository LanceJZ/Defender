#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyShot.h"
#include "EnemyMirror.h"
#include "EnemyRadar.h"
#include "Timer.h"

class Swarmer : public Model3D
{
public:
	Swarmer();
	virtual ~Swarmer();

	EnemyShot* Shots[4];

	void SetModel(Model model, Texture2D texture);
	void SetShotModel(Model model, Texture2D texture);
	void SetRadar(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	EnemyMirror Mirror;
	EnemyRadar Radar;

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	Timer* ShotTimer = new Timer();

	void FireShot();
};