#pragma once
#include "Model3D.h"
#include "EnemyRadarMirror.h"
#include "Player.h"
#include "Bomb.h"
#include "Timer.h"

class Bomber : public Model3D
{
public:
	vector<Bomb*> Bombs;

	Bomber();
	virtual ~Bomber();

	bool Initialize();
	void SetBomb(Model model);
	void SetRadar(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector2 position, float x);

private:
	Model BombModel = { 0 };
	EnemyRadarMirror RadarMirror;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	Timer DropBombTimer;

	void DropABomb();
};