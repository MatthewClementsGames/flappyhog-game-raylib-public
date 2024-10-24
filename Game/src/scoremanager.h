#pragma once

#include <memory>
#include "raylib.h"

class ScoreManager 
{
public: 
	ScoreManager(int sWidth, int sHeight);
	~ScoreManager(); 

	int GetPlayerCurrentScore() const { return playerCurrentScore; };
	int GetPlayerBestScore() const { return playerBestScore; };
	
	int GetBronzeMedalScore() const { return bronzeMedalScore; }; 
	int GetSilverMedalScore() const { return silverMedalScore; };
	int GetGoldMedalScore() const { return goldMedalScore; };
	
	void AddToScore(int score); 
	void GameOver(); 
	void Reset(); 

private:

	void SaveScore(int _newScore); 
	int LoadScore(); 

	int screenWidth{};
	int screenHeight{};

	int playerCurrentScore{0};
	int playerBestScore{0};

	const int bronzeMedalScore{10}; 
	const int silverMedalScore{20};
	const int goldMedalScore{30}; 

	Sound playerScoredSound{ LoadSound("res/audio/point-score.wav") }; 
};