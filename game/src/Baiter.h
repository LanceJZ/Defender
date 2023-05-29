#pragma once
#include "Enemy.h"

class Baiter : public Enemy
{
public:
	Baiter();
	virtual ~Baiter();

	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

private:

};