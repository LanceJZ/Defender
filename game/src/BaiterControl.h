#pragma once
#include "Common.h"
#include "Baiter.h"

class BaiterControl : Common
{
public:
	BaiterControl();
	virtual ~BaiterControl();

	std::vector<Baiter*> Baiters;

	bool Initialize();

	void SetModels(Model baiter, Model shot);
	void SetBaiterModel(Model baitar);
	void SetSounds(Sound baiter, Sound shot);

	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model BaiterModel = { 0 };
	Model BaiterShotModel = { 0 };
	Model BaiterModel = { 0 };
	Sound BaiterSound = { 0 };
	Sound BaiterShotSound = { 0 };
};