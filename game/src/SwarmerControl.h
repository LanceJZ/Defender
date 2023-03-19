#pragma once
#include "Pod.h"
#include "SharedData.h"

class SwarmerControl : Common
{
public:
	vector<Pod*> Pods;

	SwarmerControl();
	virtual ~SwarmerControl();

	bool Initialize();
	void SetPodModel(Model model);
	void SetSwarmerModel(Model model);
	void SetShotModel(Model model);
	void SetPodRadarModel(Model model);
	void SetSwarmerRadarModel(Model model);
	void SetPlayer(Player* player);
	bool BeginRun(Camera* camera);

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model PodModel = { 0 };
	Model SwarmerModel = { 0 };
	Model ShotModel = { 0 };
	Model PodRadarModel = { 0 };
	Model SwarmerRadarModel = { 0 };

	Player* ThePlayer = nullptr;
	Camera* TheCamera = nullptr;
	SharedData* Data;

	void SpawnPods(float count);
};

