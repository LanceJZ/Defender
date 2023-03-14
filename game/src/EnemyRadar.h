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

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Camera* TheCamera = nullptr;
	Player* ThePlayer = nullptr;

	void UpdateRadar();
};