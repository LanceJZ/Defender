#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Player.h"

class EnemyRadar : public Model3D
{
public:
	EnemyRadar();
	virtual ~EnemyRadar();

	void SetModel(Model model);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun(Camera* camera);
	void PositionUpdate(bool enabled, Vector3 position);
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;

	void UpdateRadar();
};