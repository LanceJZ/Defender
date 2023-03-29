#pragma once
#include "Common.h"
#include "Timer.h"
#include <string>
#include <chrono>

struct ScoreList
{
	std::string Name = "";
	int Score = 0;
};

class ScoreKeeper : Common
{
public:
	ScoreKeeper();
	virtual ~ScoreKeeper();

	bool GameOver = true;

	unsigned int Score = 21270;
	unsigned int HighScore = 21270;

	bool Initialize();
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw();

	void AddToScore(int amount);
	void ClearScore();

private:
	bool NewHighScore = false;
	bool ShowHighScores = false;
	int NewHighScoreRank = 0;
	int HighScoreSelectedLetter = 0;

	std::string HighScoreEntryText = "";
	std::string TodaysScoreListRaw = "";
	std::string AllTimeScoreListRaw = "";
	Timer HighScoretimer;


	ScoreList AllTimeScores[8];
	ScoreList TodaysScores[8];

	void Load();
	void Save();
	void SaveToday();
	void MakeNewScoreLists();
	void MakeNewTodayScoreList();
	void ConvertScoreListToString();
	void ConvertRawScoreListToArray();
	void CheckForNewHighScore(int score);
	void NewHighScoreEntry();
};

