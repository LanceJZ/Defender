#pragma once
#include "Common.h"
#include "Pod.h"

class SwarmerControl : Common
{
public:
	SwarmerControl();
	virtual ~SwarmerControl();

	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Model PodModel;
	Model SwarmerModel;
	Model ShotModel;
	Texture2D PodTexture;
	Texture2D SwarmerTexture;
	Texture2D ShotTexture;
};

