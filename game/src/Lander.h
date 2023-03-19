#pragma once
#include "Model3D.h"
#include "EnemyShot.h"
#include "Timer.h"
#include "Player.h"
#include "EnemyRadarMirror.h"
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
	bool CountChange = false;

	Lander();
	virtual ~Lander();

	EnemyShot* Shots[4];
	vector<Person*> People; //The Person Man.

	bool Initialize();
	void SetShotModel(Model model);
	void SetRadarModel(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	float GroundHoverY = 0;
	Mode CurrentMode = GoingToGround;
	EnemyRadarMirror RadarMirror;
	Timer ShotTimer;
	Player* ThePlayer = nullptr;
	Person* PersonCaptured = nullptr;

	void GoToGround();
	void SeekPersonMan();
	void FoundPersonManGoingDown();
	void GrabPersonMan();
	void SpawnMutatant();
	void FireShot();
	void FireShots();
	void CheckCollision();
	void Destroy();
};

