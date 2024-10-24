#include "floor.h"

Floor::Floor(float bScaleSize, int sHeight, int sWidth)
{
	floorScaleSize = bScaleSize;
	screenHeight = sHeight; 
	screenWidth = sWidth; 
}

Floor::~Floor()
{
	UnloadTexture(floorImage); 
}

//-------------------- Floor Tick -------------------- 
void Floor::Tick(float dt, bool isGamePaused)
{
	deltaTime = dt; 

	if (!isGamePaused)
	{
		FloorMovement(); 
	}

	DrawFloor(); 
}

//-------------------- Draw Floor -------------------- 
void Floor::DrawFloor()
{
	//Floor One
	Vector2 floorOnePos{ floorX,((float)screenHeight - (floorImage.height * floorScaleSize)) };
	DrawTextureEx(floorImage, floorOnePos, 0.0f, floorScaleSize, WHITE);
	//Floor Two
	Vector2 floorTwoPos{ floorX + floorImage.width * floorScaleSize, ((float)screenHeight - (floorImage.height * floorScaleSize)) };
	DrawTextureEx(floorImage, floorTwoPos, 0.0f, floorScaleSize, WHITE);
}

//-------------------- Floor Movement -------------------- 
void Floor::FloorMovement()
{
	floorX += floorScrollingSpeed * deltaTime;
	if (floorX <= -floorImage.width * floorScaleSize)
	{
		floorX = 0;
	}
}

//-------------------- Get Collision Rectangle -------------------- 
Rectangle Floor::GetCollisionRectangle()
{
	return Rectangle{ floorX, (float)screenHeight - (floorImage.height * floorScaleSize), (floorImage.width * floorScaleSize) * 2, floorImage.height * floorScaleSize };
}