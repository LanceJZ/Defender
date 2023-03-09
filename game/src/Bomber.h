#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "EnemyRadar.h"
#include "Player.h"
#include "Bomb.h"

class Bomber : public Model3D
{
public:
	vector<Bomb*> Bombs;

	Bomber();
	virtual ~Bomber();

	void SetModel(Model model, Texture2D texture);
	void SetBomb(Model model, Texture2D texture);
	void SetRadar(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model Bomb;
	Texture2D BombTexture;
	EnemyRadar Radar;
	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
};