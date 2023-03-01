#pragma once
#include "raylib.h"
#include "Model3D.h"
#include "Player.h"

class Person : public Model3D
{
public:
	Person();
	virtual ~Person();

	void SetModel(Model model, Texture2D texture);
	void SetPlayer(Player* player);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	Model MirrorR;
	Model MirrorL;

	Player* ThePlayer;
};

