#pragma once
#include "Enemy.h"

#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
	#define DBG_NEW new
#endif

class Bomber : public Enemy
{
public:
	std::vector<EnemyShot*> Bombs;

	Bomber();
	virtual ~Bomber();

	bool Initialize();
	void SetBomb(Model model);

	bool BeginRun(Camera *camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float x);
	void Reset();


private:
	Model BombModel = { 0 };
	Timer DropBombTimer;

	void DropABomb();
	bool CheckCollision();
	void Destroy();
};