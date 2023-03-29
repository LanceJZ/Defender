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
	NewHighScoreEntry();
}

void ScoreKeeper::Update(float deltaTime)
{

}

void ScoreKeeper::Draw()
{
	DrawText(const_cast<char*>(std::to_string(Score).c_str()), 150, 75, 45, BLUE);
}

void ScoreKeeper::AddToScore(int amount)
{
	Score += amount;
}

void ScoreKeeper::ClearScore()
{
	Score = 0;
}

void ScoreKeeper::Load()
{
	if (FileExists("HighScoreList"))
	{
		TodaysScoreListRaw = LoadFileText("HighScoreList");
		ConvertRawScoreListToArray();
	}
	else
	{
		MakeNewScoreLists();
	}
}

void ScoreKeeper::Save()
{
	SaveFileText("AllTimeHighScoreList.hs", const_cast<char*>(AllTimeScoreListRaw.c_str()));
}

void ScoreKeeper::SaveToday()
{
	SaveFileText("TodayHighScoreList.hs", const_cast<char*>(TodaysScoreListRaw.c_str()));
}

void ScoreKeeper::MakeNewScoreLists()
{
	for (int i = 0; i < 8; i++)
	{
		AllTimeScores[i].Name = "AAA";
		AllTimeScores[i].Score = 1000;
	}

	MakeNewTodayScoreList();
	Save();
}

void ScoreKeeper::MakeNewTodayScoreList()
{
	for (int i = 1; i < 8; i++)
	{
		TodaysScores[i].Name = "AAA";
		TodaysScores[i].Score = 1000;
	}

	TodaysScores[0].Name = "DRJ";
	TodaysScores[0].Score = 21270;

	ConvertScoreListToString();
	SaveToday();
}

void ScoreKeeper::ConvertScoreListToString()
{
	TodaysScoreListRaw = "";
	AllTimeScoreListRaw = "";

	for (auto score : TodaysScores)
	{
		TodaysScoreListRaw += score.Name;
		TodaysScoreListRaw += ":";
		TodaysScoreListRaw += std::to_string(score.Score);
		TodaysScoreListRaw += ",";
	}

	for (auto score : AllTimeScores)
	{
		AllTimeScoreListRaw += score.Name;
		AllTimeScoreListRaw += ":";
		AllTimeScoreListRaw += std::to_string(score.Score);
		AllTimeScoreListRaw += ",";
	}
}

void ScoreKeeper::ConvertRawScoreListToArray()
{
	int listNumber = 0;
	bool isLetter = true;
	std::string number = "";

	for (auto character : TodaysScoreListRaw)
	{
		if (isLetter)
		{
			if (character !=  58) //58 for colon.
			{
				TodaysScores[listNumber].Name.append(1, character);
			}
			else
			{
				isLetter = false;
			}
		}
		else
		{
			if (character != 44) //44 for comma.
			{
				number.append(1, character);
			}
			else
			{
				TodaysScores[listNumber].Score = std::stoi(number);
				isLetter = true;
				listNumber++;
				number = "";
			}
		}
	}

	listNumber = 0;
	isLetter = true;
	number = "";


	for (auto character : AllTimeScoreListRaw)
	{
		if (isLetter)
		{
			if (character !=  58) //58 for colon.
			{
				AllTimeScores[listNumber].Name.append(1, character);
			}
			else
			{
				isLetter = false;
			}
		}
		else
		{
			if (character != 44) //44 for comma.
			{
				number.append(1, character);
			}
			else
			{
				AllTimeScores[listNumber].Score = std::stoi(number);
				isLetter = true;
				listNumber++;
				number = "";
			}
		}
	}
}

void ScoreKeeper::CheckForNewHighScore(int score)
{
	for (int rank = 0; rank < 8; rank++)
	{
		if (score > TodaysScores[rank].Score)
		{
			if (rank < 7)
			{
				ScoreList oldScores[8];

				for (int oldRank = rank; oldRank < 8; oldRank++)
				{
					oldScores[oldRank] = TodaysScores[oldRank];
				}

				for (int newRank = rank; newRank < 7; newRank++)
				{
					TodaysScores[newRank + 1] = oldScores[newRank];
				}
			}

			TodaysScores[rank].Name = "XXX";
			TodaysScores[rank].Score = score;
			HighScoreEntryText = "___";
			NewHighScoreRank = rank;
			NewHighScore = true;
			break;
		}
	}
}

void ScoreKeeper::NewHighScoreEntry()
{
	if (IsKeyPressed(KEY_DOWN))
	{
		HighScoreSelectedLetter++;

		if (HighScoreSelectedLetter > 2)
		{
			TodaysScores[NewHighScoreRank].Name = HighScoreEntryText;
			NewHighScore = false;
			ConvertScoreListToString();
			Save();
			return;
		}
		else
		{
			HighScoreEntryText[HighScoreSelectedLetter] = (char)65;
		}
	}
	else if (IsKeyPressed(KEY_LEFT))
	{
		HighScoreEntryText[HighScoreSelectedLetter]--;

		if (HighScoreEntryText[HighScoreSelectedLetter] < (char)65)
		{
			HighScoreEntryText[HighScoreSelectedLetter] = (char)90;
		}
	}
	else if (IsKeyPressed(KEY_RIGHT))
	{
		HighScoreEntryText[HighScoreSelectedLetter]++;

		if (HighScoreEntryText[HighScoreSelectedLetter] > (char)90)
		{
			HighScoreEntryText[HighScoreSelectedLetter] = (char)65;
		}
	}
}
