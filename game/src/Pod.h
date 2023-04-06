#pragma once
#include "Enemy.h"
#include "SharedData.h"
#include "Swarmer.h"

class Pod : public Enemy
{
public:
	Pod();
	virtual ~Pod();

	bool Initialize();
	void SetData(SharedData* data);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float xVol);
	void Reset();
	void Hit();

private:
	SharedData* Data = nullptr;

	bool CheckCollision();
	void Destroy();
};