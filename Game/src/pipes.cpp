#include "pipes.h"
#include <random>

Pipes::Pipes(int sHeight, int sWidth, float aScaleSize, float pHeight, float fPosY)
{
	screenHeight = sHeight; 
	screenWidth = sWidth; 
	assetScaleSize = aScaleSize;
	playerHeight = pHeight; 
	floorPositionY = fPosY; 

	gapPlayerSizeBuffer = playerHeight / 2.0f; 

	Reset(); 
}

Pipes::~Pipes()
{
	UnloadTexture(pipeImage); 
}

//-------------------- Pipes Tick -------------------- 
void Pipes::Tick(float dt, bool isGamePaused)
{
	if (!isGamePaused)
	{
		PipesMovement(dt);
	}

	DrawPipes(); 
}

//-------------------- Draw Pipes -------------------- 
void Pipes::DrawPipes()
{
	//Draw Pipes Set One
	DrawTextureEx(pipeImage, topPipeSetOneCurrentPos, 0.0f, assetScaleSize, WHITE); 
	DrawTextureEx(pipeImage, bottomPipeSetOneCurrentPos, 180.0f, assetScaleSize, WHITE);

	//Draw Pipe Sets Two
	DrawTextureEx(pipeImage, topPipeSetTwoCurrentPos, 0.0f, assetScaleSize, WHITE);
	DrawTextureEx(pipeImage, bottomPipeSetTwoCurrentPos, 180.0f, assetScaleSize, WHITE);
}

//-------------------- Pipes Movement -------------------- 
void Pipes::PipesMovement(float dt)
{
	//Move Pipe Set One from the right to left; 
	topPipeSetOneCurrentPos.x += pipeMovementSpeed * dt; 
	bottomPipeSetOneCurrentPos.x += pipeMovementSpeed * dt;

	//Move Pipe Set Two from right to left. 
	topPipeSetTwoCurrentPos.x += pipeMovementSpeed * dt;
	bottomPipeSetTwoCurrentPos.x += pipeMovementSpeed * dt;

	if (topPipeSetOneCurrentPos.x <= 0 - (pipeImage.width * assetScaleSize))
	{
		SetNewPipesPositon(PIPE_SET_ONE, false); 
		SetHadPipeScoreBeenAdded(PIPE_SET_ONE, false);
	}

	if (topPipeSetTwoCurrentPos.x <= 0 - (pipeImage.width * assetScaleSize))
	{
		SetNewPipesPositon(PIPE_SET_TWO, false);
		SetHadPipeScoreBeenAdded(PIPE_SET_TWO, false);
	}
}

//-------------------- Set New Pipe Position -------------------- 
void Pipes::SetNewPipesPositon(PipeSet pSet, bool isFirstTimeSetup)
{
	if (pSet == PIPE_SET_ONE)
	{
		if (isFirstTimeSetup)
		{
			topPipeSetOneCurrentPos.x = (float)screenWidth + (pipeImage.width * assetScaleSize);
			bottomPipeSetOneCurrentPos.x = (float)screenWidth + (pipeImage.width * assetScaleSize);
			bottomPipeSetOneCurrentPos.x += pipeImage.width * assetScaleSize;
		}
		else
		{
			topPipeSetOneCurrentPos.x = topPipeSetTwoCurrentPos.x + spaceBetweenPipeSets;
			bottomPipeSetOneCurrentPos.x = topPipeSetTwoCurrentPos.x + spaceBetweenPipeSets;
			bottomPipeSetOneCurrentPos.x += pipeImage.width * assetScaleSize;
		}

		//Get New Gap
		Vector2 newGap = CreateNewGapPosition(topPipeSetOneCurrentPos.x);

		//Set the top pipe with the new gap. 
		topPipeSetOneCurrentPos.y = (newGap.y - gapPlayerSizeBuffer - (pipeImage.height * assetScaleSize) - gapExtraBuffer); 

		//Set the bottom pipe with the new gap. 
		bottomPipeSetOneCurrentPos.y = (newGap.y + gapPlayerSizeBuffer + (pipeImage.height * assetScaleSize) + gapExtraBuffer); 
	}
	else if (pSet == PIPE_SET_TWO)
	{
		if (isFirstTimeSetup)
		{
			topPipeSetTwoCurrentPos.x = (float)screenWidth + (pipeImage.width * assetScaleSize);
			bottomPipeSetTwoCurrentPos.x = (float)screenWidth + (pipeImage.width * assetScaleSize); 
			bottomPipeSetTwoCurrentPos.x += pipeImage.width * assetScaleSize;

			topPipeSetTwoCurrentPos.x += spaceBetweenPipeSets;
			bottomPipeSetTwoCurrentPos.x += spaceBetweenPipeSets;
		}
		else
		{
			topPipeSetTwoCurrentPos.x = topPipeSetOneCurrentPos.x + spaceBetweenPipeSets;
			bottomPipeSetTwoCurrentPos.x = topPipeSetOneCurrentPos.x + spaceBetweenPipeSets;
			bottomPipeSetTwoCurrentPos.x += pipeImage.width * assetScaleSize;
		}

		//Get New Gap
		Vector2 newGap = CreateNewGapPosition(topPipeSetTwoCurrentPos.x);

		//Set the top pipe with the new gap. 
		topPipeSetTwoCurrentPos.y = (newGap.y - gapPlayerSizeBuffer - (pipeImage.height * assetScaleSize) - gapExtraBuffer);

		//Set the bottom pipe with the new gap. 
		bottomPipeSetTwoCurrentPos.y = (newGap.y + gapPlayerSizeBuffer + (pipeImage.height * assetScaleSize) + gapExtraBuffer);
	}
}

//-------------------- Create New Pipe Gap Position -------------------- 
Vector2 Pipes::CreateNewGapPosition(float pipeXPos)
{
	return Vector2{pipeXPos, GetRandom( 0 + gapPosYBuffer, floorPositionY - gapPosYBuffer)};
}

//-------------------- Get Random float -------------------- 
float Pipes::GetRandom(float numOne, float numTwo)
{
	std::random_device seed; 
	std::mt19937 gen{ seed() }; 
	std::uniform_int_distribution<> dist{ (int) numOne, (int) numTwo}; 
	int rand = dist(gen); 
	return (float)rand; 
}

//-------------------- Get Pipe Collision Rectangle -------------------- 
Rectangle Pipes::GetPipeCollisionRec(Pipe _pipe)
{
	if (_pipe == TOP_PIPE_SET_ONE)
	{
		return Rectangle{ topPipeSetOneCurrentPos.x, topPipeSetOneCurrentPos.y, pipeImage.width * assetScaleSize, pipeImage.height * assetScaleSize }; 
	}
	else if (_pipe == BOTTOM_PIPE_SET_ONE)
	{
		return Rectangle{ bottomPipeSetOneCurrentPos.x + (-pipeImage.width * assetScaleSize), bottomPipeSetOneCurrentPos.y + (-pipeImage.height * assetScaleSize), pipeImage.width * assetScaleSize, pipeImage.height * assetScaleSize};
	}
	else if (_pipe == TOP_PIPE_SET_TWO)
	{
		return Rectangle{ topPipeSetTwoCurrentPos.x, topPipeSetTwoCurrentPos.y, pipeImage.width * assetScaleSize, pipeImage.height * assetScaleSize };
	}
	else
	{
		return Rectangle{ bottomPipeSetTwoCurrentPos.x + (-pipeImage.width * assetScaleSize), bottomPipeSetTwoCurrentPos.y + (-pipeImage.height * assetScaleSize), pipeImage.width * assetScaleSize, pipeImage.height * assetScaleSize };
	}
}

//-------------------- Get Pipe Score Collision Rectangle -------------------- 
Rectangle Pipes::GetPipeScoreCollisionRec(PipeSet _pipeSet)
{
	if (_pipeSet == PIPE_SET_ONE)
	{
		return Rectangle{
			topPipeSetOneCurrentPos.x + ((float) pipeImage.width * assetScaleSize),
			topPipeSetOneCurrentPos.y + pipeImage.height * assetScaleSize,
			50.0f, 
			(bottomPipeSetOneCurrentPos.y - (float)pipeImage.height * assetScaleSize) - (topPipeSetOneCurrentPos.y + (float)pipeImage.height * assetScaleSize)
		};
	}
	else
	{
		return Rectangle{
			topPipeSetTwoCurrentPos.x + ((float)pipeImage.width * assetScaleSize),
			topPipeSetTwoCurrentPos.y + pipeImage.height * assetScaleSize,
			50.0f,
			(bottomPipeSetTwoCurrentPos.y - (float)pipeImage.height * assetScaleSize) - (topPipeSetTwoCurrentPos.y + (float)pipeImage.height * assetScaleSize)
		}; 
	}
}

//-------------------- Get Has Pipe Score Been Added -------------------- 
bool Pipes::GetHasPipeScoreBeenAdded(PipeSet _pipeSet)
{
	if (_pipeSet == PIPE_SET_ONE)
	{
		return hasPipeSetOneScoreBeenAdded;
	}
	else
	{
		return hasPipeSetTwoScoreBeenAdded;
	}
}

//-------------------- Set Has Pipe Score Been Added -------------------- 
void Pipes::SetHasPipeScoreBeenAdded(PipeSet _pipeSet, bool _bool)
{
	if (_pipeSet == PIPE_SET_ONE)
	{
		hasPipeSetOneScoreBeenAdded = _bool; 
	}
	else
	{
		hasPipeSetTwoScoreBeenAdded = _bool;
	}
}

//-------------------- Reset -------------------- 
void Pipes::Reset()
{
	//Set Pipe Set One Back to it's starting position.  
	SetNewPipesPositon(PIPE_SET_ONE, true);
	SetHasPipeScoreBeenAdded(PIPE_SET_ONE, false);

	//Set Pipe Set Two Back to it's starting positon. 
	SetNewPipesPositon(PIPE_SET_TWO, true);
	SetHasPipeScoreBeenAdded(PIPE_SET_TWO, false);
}