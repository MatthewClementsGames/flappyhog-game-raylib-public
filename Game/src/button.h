#pragma once
#include "raylib.h"

class Button
{
public: 
	Button(const char* imagePath, float aScaleSize, Vector2 buttonPos);
	~Button(); 

	void Tick(); 
	bool IsPressed(Vector2 mousePos, bool mouseButtonPressed); 

private: 

	void SetPosition(Vector2 newPos);

	Texture2D buttonImage{};
	Vector2 buttonPos{}; 
	float buttonScaleSize{}; 
};