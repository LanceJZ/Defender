#pragma once
#include "Model3D.h"
#include "Player.h"
#include "EnemyRadarMirror.h"

class Person : public Model3D
{
public:
	bool BeingCaptured = false;

	virtual ~Person();

	void SetRadar(Model model);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	EnemyRadarMirror RadarMirror;

	Player* ThePlayer = nullptr;
};