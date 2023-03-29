#pragma once
#include "Model3D.h"
#include "Player.h"
#include "EnemyRadarMirror.h"
#include "ExplosionControl.h"
#include "ScoreKeeper.h"

class Person : public Model3D
{
public:
	enum PersonState
	{
		OnGround,
		GoingDown,
		CaughtByPlayer,
		TargetedByLander
	};

	PersonState State = OnGround;
	bool CountChanged = false;

	Person();
	virtual ~Person();

	bool Initialize();
	void SetRadar(Model &model);
	void SetPlayer(Player *player);
	void SetSounds(Sound& caught, Sound& left, Sound& splat);
	void SetExplosion(ExplosionControl* explosion);
	void SetScore(ScoreKeeper* score);
	bool BeginRun(Camera *camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void Dropped();
	void Destroy();
	void Reset();

private:
	int ScoreLandedAmount = 250; //Landed on own;
	int ScoreCaughtAmount = 500; //Player caught.
	int ScoreDroppedAmount = 500; //Player dropped off player.
	float DroppedY = 0;
	EnemyRadarMirror RadarMirror;

	Sound CaughtSound = { 0 };
	Sound LeftSound = { 0 };
	Sound SplatSound = { 0 };

	ExplosionControl* Explosion = nullptr;
	Player *ThePlayer = nullptr;
	ScoreKeeper* Score = nullptr;

	void Falling();
	void GoingForARide();
	void CheckCollision();
};