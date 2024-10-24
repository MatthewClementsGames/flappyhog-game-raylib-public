#pragma once
#include <raylib.h>

class Pipes
{
public:
	Pipes(int sHeight, int sWidth, float aScaleSize, float pHeight, float fPosX);
	~Pipes();

	enum PipeSet
	{
		PIPE_SET_ONE,
		PIPE_SET_TWO
	};

	enum Pipe
	{
		TOP_PIPE_SET_ONE, 
		BOTTOM_PIPE_SET_ONE, 
		TOP_PIPE_SET_TWO,
		BOTTOM_PIPE_SET_TWO
	};

	void Tick(float dt, bool isGamePaused);
	void Reset();

	Rectangle GetPipeCollisionRec(Pipe _pipe); 
	Rectangle GetPipeScoreCollisionRec(PipeSet _pipeSet);

	bool GetHasPipeScoreBeenAdded(PipeSet _pipeSet); 
	void SetHasPipeScoreBeenAdded(PipeSet _pipeSet, bool _bool); 
	
private: 

	void DrawPipes();
	void PipesMovement(float dt);
	Vector2 CreateNewGapPosition(float pipeXPos);
	void SetNewPipesPositon(PipeSet pSet, bool firstTimeSetup); 
	float GetRandom(float numOne, float numTwo);

	//Information passed in via the construction parameters
	int screenHeight{};
	int screenWidth{};
	float assetScaleSize{};
	float playerHeight{};
	float floorPositionY{};

	//Pipes
	Texture2D pipeImage{ LoadTexture("res/images/pipe.png") }; 
	//Pipe Set One
	Vector2 topPipeSetOneCurrentPos{}; 
	Vector2 bottomPipeSetOneCurrentPos{};

	//Pipe Set Two
	Vector2 topPipeSetTwoCurrentPos{};
	Vector2 bottomPipeSetTwoCurrentPos{};

	float spaceBetweenPipeSets{ 500.0f }; //The space between the X of pipe set one and pipe set two. 

	//Pipe Gap Extras
	float gapPlayerSizeBuffer{}; //A buffer is needed each side of the gap position to ensure the player is always able to fit. 
	float gapExtraBuffer{35.0f}; //Another buffer as the gap can't just be 'enough' for the player to get through. 
	float gapPosYBuffer{ 145.0f }; //This is a buffer from both the top of the screen and the floor Y pos so that a gap position is not spawning at 0 or exactly on the floor Y. 
	
	//Pipe Movement
	float pipeMovementSpeed{-200.f};

	//Pipe Score Bools
	bool hasPipeSetOneScoreBeenAdded{ false }; 
	bool hasPipeSetTwoScoreBeenAdded{ false }; 
};