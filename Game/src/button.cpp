#include "button.h"

Button::Button(const char* imagePath, float uiScaleSize, Vector2 buttonPos)
{
	buttonImage = LoadTexture(imagePath);
	buttonScaleSize = uiScaleSize;

	SetPosition(buttonPos);
}

Button::~Button()
{
	UnloadTexture(buttonImage); 
}

//-------------------- Button Tick -------------------- 
void Button::Tick()
{
	DrawTextureEx(buttonImage, buttonPos, 0.0f, buttonScaleSize, WHITE);
}

//-------------------- Button Set Position -------------------- 
void Button::SetPosition(Vector2 newPos)
{
	buttonPos = newPos; 

	//This will center the image in the position we want the button to be. 
	buttonPos.x = buttonPos.x - ((float)buttonImage.width * buttonScaleSize) / 2.0f;
	buttonPos.y = buttonPos.y - ((float)buttonImage.height * buttonScaleSize) / 2.0f;
}

//-------------------- Is Button Pressed -------------------- 
bool Button::IsPressed(Vector2 mousePos, bool mouseButtonPressed)
{
	Rectangle buttonRec{ buttonPos.x, buttonPos.y, buttonImage.width * buttonScaleSize, buttonImage.height * buttonScaleSize };

	if (CheckCollisionPointRec(mousePos, buttonRec) && mouseButtonPressed)
	{
		return true; 
	}
	return false; 
}


