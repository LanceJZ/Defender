#pragma once
#include "Model3D.h"
#include "Timer.h"

class ParticleCube : public Model3D
{
public:
	ParticleCube();
	virtual ~ParticleCube();

	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, float time);

private:
	Timer LifeTimer;
};
