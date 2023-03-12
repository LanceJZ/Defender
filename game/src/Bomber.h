#pragma once
#include "Model3D.h"
#include "EnemyRadar.h"
#include "EnemyMirror.h"
#include "Player.h"
#include "Bomb.h"
#include "Timer.h"

class Bomber : public Model3D
{
public:
	vector<Bomb*> Bombs;

	Bomber();
	virtual ~Bomber();

	void SetBomb(Model model);
	void SetRadar(Model model);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector2 position, float x);

private:
	Model BombModel = { 0 };
	EnemyMirror Mirror;
	EnemyRadar Radar;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	Timer* DropBombTimer = new Timer();

	void DropABomb();
};