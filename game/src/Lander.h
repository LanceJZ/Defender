#pragma once
#include "Model3D.h"
#include "EnemyShot.h"
#include "Timer.h"
#include "Enemy.h"
#include "Person.h"

enum StateList
{
	GoingToGround,
	Seek,
	FoundPersonMan,
	PickUpPersonMan,
	Mutate
};

class Lander : public Enemy
{
public:
	Lander();
	virtual ~Lander();

	bool MutateLander = false;
	Person* People[10]; //The Person Man. Reference filled by class in charge.

	bool Initialize();
	void SetShotModel(Model model);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);
	void Reset();

private:
	float GroundHoverY = 0;
	StateList State = GoingToGround;
	Person* PersonCaptured = nullptr;

	void GoToGround();
	void SeekPersonMan();
	void FoundPersonManGoingDown();
	void GrabPersonMan();
	void SpawnMutatant();
	void FireShot();
	bool CheckCollision();
	void Destroy();
};

