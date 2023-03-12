#pragma once
#include "Common.h"
#include "Pod.h"

class SwarmerControl : Common
{
public:
	vector<Pod*> Pods;

	SwarmerControl();
	virtual ~SwarmerControl();

	void SetPodModel(Model model);
	void SetSwarmerModel(Model model);
	void SetShotModel(Model model);
	bool Initialize();
	bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model PodModel = { 0 };
	Model SwarmerModel = { 0 };
	Model ShotModel = { 0 };
};

