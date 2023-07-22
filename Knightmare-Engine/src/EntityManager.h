#pragma once
#include <memory>
#include <vector>
#include "Entity.h"
#include "LineModel.h"
#include "Model3D.h"
#include "Timer.h"

class EntityManager : Common
{
public:
	EntityManager();
	virtual ~EntityManager();

	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw3D();

	size_t AddEntity(Entity* entity);
	size_t AddEntity();
	size_t AddLineModel(LineModel* model);
	size_t AddLineModel(LineModelPoints model);
	size_t AddLineModel();
	size_t AddModel3D(Model3D* model, Camera* camera);
	size_t AddModel3D(Model model, Camera* camera);
	size_t AddTimer();
	size_t AddCommon(Common* common);

	Entity* CreateEntity();
	LineModel* CreateLineModel();
	Model3D* CreateModel3D(Model model, Camera* camera);

	std::vector<Entity*> Entities;
	std::vector<LineModel*> LineModels;
	std::vector<Model3D*> Model3Ds;
	std::vector<Timer*> Timers;
	std::vector<Common*> Commons;

private:
	Camera* TheCamera = {};
};

