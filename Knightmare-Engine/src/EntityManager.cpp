#include "EntityManager.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	for (auto model : LineModels)
	{
		delete(model);
	}

	for (auto model : Model3Ds)
	{
		delete(model);
	}

	for (auto entity : Entities)
	{
		delete(entity);
	}

	for (auto timer : Timers)
	{
		delete(timer);
	}

	for (auto common : Commons)
	{
		delete(common);
	}

	Entities.clear();
	LineModels.clear();
	Model3Ds.clear();
	Timers.clear();
	Commons.clear();
}

bool EntityManager::BeginRun()
{
	for (auto model3D : Model3Ds)
	{
		model3D->BeginRun(TheCamera);
	}

	for (auto lineModel : LineModels)
	{
		lineModel->BeginRun();
	}

	for (auto common : Commons)
	{
		common->BeginRun();
	}

	return true;
}

void EntityManager::Input()
{
	for (auto lineModel : LineModels)
	{
		lineModel->Input();
	}

	for (auto model3D : Model3Ds)
	{
		model3D->Input();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto entity : Entities)
	{
		if (entity->Enabled) entity->Update(deltaTime);
	}

	for (auto lineModel : LineModels)
	{
		if (lineModel->Enabled)	lineModel->Update(deltaTime);
	}

	for (auto model3D : Model3Ds)
	{
		if (model3D->Enabled) model3D->Update(deltaTime);
	}

	for (auto timer : Timers)
	{
		timer->Update(deltaTime);
	}

	for (auto common : Commons)
	{
		common->Update();
	}
}

void EntityManager::Draw3D()
{
	for (auto entity : Entities)
	{
		if (entity->Enabled) entity->Draw();
	}

	for (auto lineModel : LineModels)
	{
		if (lineModel->Enabled)	lineModel->Draw();
	}

	for (auto model3D : Model3Ds)
	{
		if (model3D->Enabled) model3D->Draw();
	}
}

size_t EntityManager::AddEntity(Entity* entity)
{
	size_t entityNumber = Entities.size();
	Entities.push_back(entity);
	Entities[entityNumber]->Initialize();

	return entityNumber;
}

size_t EntityManager::AddEntity()
{
	size_t entityNumber = Entities.size();
	Entity* newEntity = new Entity();
	Entities.push_back(newEntity);
	Entities[entityNumber]->Initialize();

	return entityNumber;
}

size_t EntityManager::AddLineModel(LineModel* model)
{
	size_t number = LineModels.size();

	LineModels.push_back(model);
	LineModels[number]->Initialize();

	return number;
}

size_t EntityManager::AddLineModel(LineModelPoints model)
{
	size_t number = LineModels.size();

	LineModels.push_back(new LineModel());
	LineModels[number]->SetModel(model);
	LineModels[number]->Initialize();

	return number;
}

size_t EntityManager::AddLineModel()
{
	size_t number = LineModels.size();

	LineModels.push_back(new LineModel());
	LineModels[number]->Initialize();

	return number;
}

size_t EntityManager::AddModel3D(Model3D* model, Camera* camera)
{
	size_t modelNumber = Model3Ds.size();

	TheCamera = camera;
	Model3Ds.push_back(model);
	Model3Ds[modelNumber]->Initialize();

	return modelNumber;
}

size_t EntityManager::AddModel3D(Model model, Camera* camera)
{
	size_t modelNumber = Model3Ds.size();
	Model3Ds.push_back(new Model3D());
	Model3Ds[modelNumber]->SetModel(model, 1.0f);
	Model3Ds[modelNumber]->Initialize();

	return modelNumber;
}

size_t EntityManager::AddTimer()
{
	size_t timerNumber = Timers.size();
	Timers.push_back(new Timer());

	return timerNumber;
}

size_t EntityManager::AddCommon(Common* common)
{
	size_t commonNumber = Commons.size();
	Commons.push_back(common);
	Commons[commonNumber]->Initialize();

	return commonNumber;
}

Entity* EntityManager::CreateEntity()
{
	Entity* newEntity = new Entity();
	Entities.push_back(newEntity);
	newEntity->Initialize();
	newEntity->BeginRun();

	return newEntity;
}

LineModel* EntityManager::CreateLineModel()
{
	LineModel* newLineModel = new LineModel();
	LineModels.push_back(newLineModel);
	newLineModel->Initialize();
	newLineModel->BeginRun();

	return newLineModel;
}

Model3D* EntityManager::CreateModel3D(Model model, Camera* camera)
{
	Model3D* newModel3D = new Model3D();
	Model3Ds.push_back(newModel3D);
	newModel3D->SetModel(model, 1.0f);
	newModel3D->Initialize();
	newModel3D->BeginRun(camera);

	return newModel3D;
}
