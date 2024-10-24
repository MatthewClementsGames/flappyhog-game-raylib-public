#pragma once
#include <raylib.h>

class Player
{
public: 
	Player(float aScaleSize, int sHeight, int sWidth);
	~Player();

	void Tick(float dt, bool isGamePaused); 
	void Reset(); 
	void PlayerPlayerCrashSound(int soundInt); 

	Rectangle GetCollisionRectangle(); 
private:

	int screenHeight{};
	int screenWidth{};
	float playerAssetScaleSize{};

	void PlayerJump();
	void MaxVelocityCheck(); 

	Texture2D playerImage{ LoadTexture("res/images/hog.png") };
	Vector2 playerStartPos{}; 
	Vector2 playerCurrentPos{}; 

	float playerCurrentVelocity{ 0.0f };
	const float playerJumpVelocity{-350.f}; 
	const float playerGravity{825.0f};

	const float playerCollisionBoxXPadding{ 15.0f }; 
	const float playerCollisionBoxYPadding{ 30.0f };

	Sound playerPipesCrashSound{ LoadSound("res/audio/hog-crash.wav") };
	Sound playerWaterCrashSound{ LoadSound("res/audio/hog-crash-water.wav") }; 
};