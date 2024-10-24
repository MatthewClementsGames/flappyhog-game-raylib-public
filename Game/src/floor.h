#pragma once
#include <raylib.h>

class Floor
{
public: 
	Floor(float bScaleSize, int sHeight, int sWidth);
	~Floor(); 

	void Tick(float dt, bool isGamePaused);

	Rectangle GetCollisionRectangle(); 

private: 

	void FloorMovement(); 
	void DrawFloor(); 

	int screenHeight{};
	int screenWidth{};
	float floorScaleSize{};
	float deltaTime{};

	Texture2D floorImage{ LoadTexture("res/images/water.png") }; 

	float floorScrollingSpeed {-100.0f};
	float floorX{ 0.0f }; 
};
