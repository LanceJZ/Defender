#pragma once
#include "Common.h"
#include <string>

class ScoreKeeper : Common
{
public:
	ScoreKeeper();
	virtual ~ScoreKeeper();

	unsigned int Score = 153725;
	unsigned int HighScore = 0;

	bool Initialize();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:

};

