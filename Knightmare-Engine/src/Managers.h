#pragma once
#include "ContentManager.h"
#include "EntityManager.h"

class Managers : Common
{
public:
	ContentManager CM;
	EntityManager EM;


	Managers();
	virtual ~Managers();

	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);

private:

};