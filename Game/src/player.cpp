#include "player.h"

Player::Player(float aScaleSize, int sHeight, int sWidth)
{
	playerAssetScaleSize = aScaleSize; 

	screenHeight = sHeight; 
	screenWidth = sWidth; 

	playerStartPos.x = ((float) screenWidth / 2.0f) - ((float) playerImage.width / 2.0f) * playerAssetScaleSize;
	playerStartPos.y = 300.0f; 

	Reset(); 

	SetSoundVolume(playerPipesCrashSound, 0.6f); 
	SetSoundVolume(playerWaterCrashSound, 0.6f);
}

Player::~Player()
{
	UnloadTexture(playerImage); 
	UnloadSound(playerWaterCrashSound); 
	UnloadSound(playerPipesCrashSound); 
}

//-------------------- Player Tick -------------------- 
void Player::Tick(float dt, bool isGamePaused)
{	
	if (!isGamePaused)
	{
		playerCurrentVelocity += playerGravity * dt;

		PlayerJump();

		MaxVelocityCheck();

		playerCurrentPos.y += playerCurrentVelocity * dt;
	}

	DrawTextureEx(playerImage, playerCurrentPos, 0.0f, playerAssetScaleSize, WHITE); 
}

//-------------------- Player Jump -------------------- 
void Player::PlayerJump()
{
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		playerCurrentVelocity += playerJumpVelocity; 
	}
}

//-------------------- Max Velocity Check -------------------- 
void Player::MaxVelocityCheck()
{
	if (playerCurrentVelocity < playerJumpVelocity)
	{
		playerCurrentVelocity = playerJumpVelocity; 
	}

	if (playerCurrentVelocity > playerGravity)
	{
		playerCurrentVelocity = playerGravity; 
	}
}

//-------------------- Get Collision Rectangle -------------------- 
Rectangle Player::GetCollisionRectangle()
{
	return Rectangle{playerCurrentPos.x, playerCurrentPos.y + playerCollisionBoxYPadding, playerImage.width * playerAssetScaleSize - playerCollisionBoxXPadding, playerImage.height * playerAssetScaleSize - playerCollisionBoxYPadding};
}

void Player::PlayerPlayerCrashSound(int soundInt)
{
	//if int is 1 play the pipes crash sound
	//if int is 2 play the water crash sound. 
	if (soundInt == 1)
	{
		PlaySound(playerPipesCrashSound);
	}
	else if (soundInt == 2)
	{
		PlaySound(playerWaterCrashSound);
	}
}

//-------------------- Reset -------------------- 
void Player::Reset()
{
	playerCurrentPos = playerStartPos;
	playerCurrentVelocity = 0.0f; 
}