#include "BaiterControl.h"

BaiterControl::BaiterControl()
{

}

BaiterControl::~BaiterControl()
{
	UnloadModel(BaiterModel);
	//UnloadSound(BaiterSound);
	//UnloadSound(BaiterShotSound);
}

bool BaiterControl::Initialize()
{

	return false;
}

void BaiterControl::SetModels(Model baiter, Model shot)
{
	BaiterModel = baiter;
	BaiterShotModel = shot;
}

void BaiterControl::SetRadarModel(Model radar)
{
	RadarModel = radar;
}

void BaiterControl::SetSounds(Sound baiter, Sound shot)
{
	BaiterSound = baiter;
	BaiterShotSound = shot;
}

bool BaiterControl::BeginRun()
{

	return false;
}

void BaiterControl::Input()
{

}

void BaiterControl::Update(float deltaTime)
{

}

void BaiterControl::Draw()
{

}