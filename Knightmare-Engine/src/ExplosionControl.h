#pragma once
#include "Common.h"
#include "ParticleCube.h"

#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
	#define DBG_NEW new
#endif

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
	void Reset();

private:
	float Xmult = 0;
	float MirrorMult = 0;
	std::vector<ParticleCube*> Particles;

	Model CubeModel = { 0 };
	Camera* TheCamera = nullptr;

	int SpawnPool();
};

