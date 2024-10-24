#include "scoremanager.h"
#include <fstream>

ScoreManager::ScoreManager(int sWidth, int sHeight)
{
	screenWidth = sWidth; 
	screenHeight = sHeight; 

	playerBestScore = LoadScore(); 
}

ScoreManager::~ScoreManager()
{
	UnloadSound(playerScoredSound); 
}

//-------------------- Game Over -------------------- 
void ScoreManager::GameOver()
{
	if (playerCurrentScore > playerBestScore)
	{
		playerBestScore = playerCurrentScore; 
		SaveScore(playerBestScore); 
	}
}

//-------------------- Add to Score -------------------- 
void ScoreManager::AddToScore(int score)
{
	playerCurrentScore += score; 
	PlaySound(playerScoredSound); 
}

//-------------------- Save Score -------------------- 
void ScoreManager::SaveScore(int newScore)
{
	std::ofstream myWriteFile; 
	myWriteFile.open("res/saves/highscore.txt", std::ofstream::out); 
	if (myWriteFile.is_open())
	{
		myWriteFile << newScore; 
	}

	myWriteFile.close(); 
}

//-------------------- Load Score -------------------- 
int ScoreManager::LoadScore()
{
	int score{};
	std::ifstream myReadFile;
	myReadFile.open("res/saves/highscore.txt");
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> score; 
			myReadFile.close(); 
		}
	}
	return score; 
}

//-------------------- Reset -------------------- 
void ScoreManager::Reset()
{
	playerCurrentScore = 0; 
}
