#pragma once
#include "Entity.h"

class Model3D : public Entity
{
public:
	Vector3 ModelPosition = { 0 };
	float ModelScale = 1;
	Color ModelColor = WHITE;
	Color TheColor = WHITE;
	Model TheModel;

	bool Initialize();
	virtual void LoadModel(Model model, Texture2D texture);
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void AddChild(Model3D* child);

private:
	vector <Model3D*> Children;
	vector <Model3D*> Parents;

	virtual void AddChildren(Model3D* child);

};

