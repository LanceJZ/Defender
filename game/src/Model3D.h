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

	Model3D();
	~Model3D();

	virtual bool Initialize();
	virtual void LoadModel(Model &model, Texture2D &texture);
	virtual bool BeginRun(Camera* camera);
	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void AddChild(Model3D* child);
	virtual void SetModel(Model &model, float scale);
	virtual void SetModelCopy(Model model, float scale);
	virtual Model& GetModel();
	void Unload();

private:
	Model TheModel;
	Camera* TheCamera = nullptr;
	std::vector <Model3D*> Children;
	std::vector <Model3D*> Parents;

	virtual void AddChildren(Model3D* child);
};

