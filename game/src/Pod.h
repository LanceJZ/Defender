#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Swarmer.h"
#include "EnemyMirror.h"
#include "EnemyRadar.h"

class Pod : public Model3D
{
public:
	Pod();
	virtual ~Pod();

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
};