#pragma once
#include "Model3D.h"
#include "Player.h"
#include "EnemyRadar.h"
#include "EnemyMirror.h"

class Person : public Model3D
{
public:
	bool BeingCaptured = false;

	virtual ~Person();

	void SetModel(Model model, Texture2D texture);
	void SetRadar(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	void SetCamera(Camera* camera);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	EnemyMirror Mirror;
	EnemyRadar Radar;

	Player* ThePlayer = nullptr;
};