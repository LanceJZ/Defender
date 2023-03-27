#pragma once
#include "Common.h"
#include "Model3D.h"

class EnemyMirror : Common
{
public:
	EnemyMirror();
	virtual ~EnemyMirror();

	bool Initialize();
	void SetModel(Model model, float scale);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void PositionUpdate(bool enabled, Vector3 position);
	void EnabledUpdate(bool enabled);
	void DeleteModels();

private:
	float X = 0;
	float Xmult = 0;
	float MirrorMult = 0;
	Model3D MirrorR;
	Model3D MirrorL;
};

