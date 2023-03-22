#pragma once
#include "Entity.h"

class Model3D : public Entity
{
public:
	bool Cull = true;
	float ModelScale = 1;
	Vector2 ViewableArea = { 0 };
	Vector3 ModelPosition = { 0 };
	Color ModelColor = WHITE;
	Color TheColor = WHITE;

	bool Initialize();
	virtual void LoadModel(Model model, Texture2D texture);
	virtual bool BeginRun(Camera* camera);
	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void AddChild(Model3D* child);
	virtual void SetModel(Model model, float scale);
	virtual Model GetModel();

private:
	Model TheModel;
	Camera* TheCamera = nullptr;
	vector <Model3D*> Children;
	vector <Model3D*> Parents;

	virtual void AddChildren(Model3D* child);
};

