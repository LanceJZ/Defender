#pragma once
#include "Common.h"
#include "ParticleCube.h"

class ExplosionControl : Common
{
public:
	ExplosionControl();
	virtual ~ExplosionControl();

	bool Initialize();
	void SetCubeModel(Model model);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position, int count, float time);

private:
	float Xmult = 0;
	float MirrorMult = 0;
	std::vector<ParticleCube*> Particles;
	Model CubeModel = { 0 };
	Camera* TheCamera = nullptr;

	int SpawnPool();
};

