#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Player.h"

class EnemyRadar : public Model3D
{
public:
	EnemyRadar();
	virtual ~EnemyRadar();

	void SetModel(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Camera* TheCamera;
	Player* ThePlayer;

	void UpdateRadar();
};