#include "ScoreKeeper.h"

ScoreKeeper::ScoreKeeper()
{

}

ScoreKeeper::~ScoreKeeper()
{
}

bool ScoreKeeper::Initialize()
{

	return false;
}

bool ScoreKeeper::BeginRun()
{

	return false;
}

void ScoreKeeper::Input()
{

}

void ScoreKeeper::Update(float deltaTime)
{

}

void ScoreKeeper::Draw()
{
	DrawText(const_cast<char*>(std::to_string(Score).c_str()), 150, 75, 45, BLUE);
}