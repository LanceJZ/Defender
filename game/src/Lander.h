#pragma once
#include "Enemy.h"
#include "Person.h"

enum StateList
{
	GoingToGround,
	Seek,
	FoundPersonMan,
	TakePersonMan,
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
	void SetShotModel(Model &model);
	void SetPersonSound(Sound& grabbed, Sound& dropped, Sound& mutate);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void Reset();
	void Hit();

private:
	float GroundHoverY = 0;
	StateList State = GoingToGround;
	Sound PersonGrabbedSound = { 0 };
	Sound PersonDroppedSound = { 0 };
	Sound MutateSound = { 0 };
	Person* PersonTarget = nullptr;

	void GoToGround();
	void SeekPersonMan();
	void FoundPersonManGoingDown();
	void GrabPersonMan();
	void SpawnMutatant();
	void FireShot();
	bool CheckCollision();
	void Destroy();
};

