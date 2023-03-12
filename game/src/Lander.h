#pragma once
#include "Model3D.h"
#include "EnemyShot.h"
#include "Timer.h"
#include "Player.h"
#include "EnemyRadar.h"
#include "EnemyMirror.h"
#include "Person.h"

enum Mode
{
	GoingToGround,
	Seek,
	FoundPersonMan,
	PickUpPersonMan,
	Mutate
};

class Lander : public Model3D
{
public:
	bool MutateLander = false;

	Lander();
	virtual ~Lander();

	EnemyShot* Shots[4];
	vector<Person*> People; //The Person Man.

	void SetShotModel(Model model);
	void SetRadarModel(Model model);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	float GroundHoverY = 0;
	Mode CurrentMode = GoingToGround;
	EnemyMirror Mirror;
	EnemyRadar Radar;
	Timer* ShotTimer = new Timer();
	Player* ThePlayer = nullptr;
	Person* PersonCaptured = nullptr;

	void GoToGround();
	void SeekPersonMan();
	void FoundPersonManGoingDown();
	void GrabPersonMan();
	void SpawnMutatant();
	void FireShot();
	void FireShots();
};

