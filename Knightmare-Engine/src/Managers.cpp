#include "Managers.h"

Managers::Managers()
{
}

Managers::~Managers()
{
}

bool Managers::Initialize()
{
	CM.Initialize();

	return false;
}

bool Managers::BeginRun()
{
	CM.BeginRun();
	EM.BeginRun();

	return false;
}

void Managers::Update(float deltaTime)
{

}