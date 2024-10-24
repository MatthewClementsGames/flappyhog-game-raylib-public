#include "game.h"
#include <raylib.h>
#include "projectsettings.h"
#include "scenemanager.h"
#include "scoremanager.h"
#include "uimanager.h"
#include "floor.h"
#include "player.h"
#include "pipes.h"

Game::Game()
{
	//Projects Settings Setup
	projectSettingsPtr = std::make_shared<ProjectSettings>(); 

	InitWindow(projectSettingsPtr->GetScreenWidth(), projectSettingsPtr->GetScreenHeight(), "FLAPPY HOG!");

	InitAudioDevice(); 

	//Scene Manager Setup
	sceneManagerPtr = std::make_shared<SceneManager>(
		projectSettingsPtr->GetScreenWidth(),
		projectSettingsPtr->GetScreenHeight(),
		projectSettingsPtr->GetBackgroundScaleSize(),
		projectSettingsPtr->GetRaylibIconScaleSize()
	);

	//Score Manager Setup
	scoreManagerPtr = std::make_shared<ScoreManager>(
		projectSettingsPtr->GetScreenWidth(),
		projectSettingsPtr->GetScreenHeight()
	);

	//UI Manager Setup
	uiManagerPtr = std::make_shared<UIManager>(
		projectSettingsPtr->GetScreenWidth(),
		projectSettingsPtr->GetScreenHeight(),
		projectSettingsPtr->GetUIAssetsScaleSize(), 
		sceneManagerPtr, 
		scoreManagerPtr
	);

	SetTargetFPS(60); 

	//Setup the Floor
	floorPtr = std::make_shared<Floor>(projectSettingsPtr->GetBackgroundScaleSize(), projectSettingsPtr->GetScreenHeight(),
		projectSettingsPtr->GetScreenWidth());

	//Setup the Player
	playerPtr = std::make_shared<Player>(projectSettingsPtr->GetAssetsScaleSize(), projectSettingsPtr->GetScreenHeight(),
		projectSettingsPtr->GetScreenWidth());

	//Setup the Pipes
	pipesPtr = std::make_shared<Pipes>(projectSettingsPtr->GetScreenHeight(),
		projectSettingsPtr->GetScreenWidth(), projectSettingsPtr->GetAssetsScaleSize(),
		playerPtr->GetCollisionRectangle().height, floorPtr->GetCollisionRectangle().y);

	while (!exitGame)
	{
		if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) { exitGame = true; }

		BeginDrawing();
		ClearBackground(WHITE);

		sceneManagerPtr->Tick(projectSettingsPtr->GetDeltaTime());

		switch (sceneManagerPtr->GetCurrentScene())
		{
		case SceneManager::SCENE_RAYLIB_SPLASH_SCREEN:
			break;
		case SceneManager::SCENE_MC_SPLASH_SCREEN:
			break;
		case SceneManager::SCENE_MAIN_MENU:
			MainMenu();
			break;
		case SceneManager::SCENE_GAME:
			GamePlay(); 
			break;
		case SceneManager::SCENE_PAUSE:
			GamePaused(); 
			break;
		case SceneManager::SCENE_GAME_OVER:
			GameOver(); 
			break;
		}

		uiManagerPtr->Tick(projectSettingsPtr->GetDeltaTime());

		EndDrawing();
	}

	CloseAudioDevice(); 

	CloseWindow();
}

//-------------------- Main Menu -------------------- 
void Game::MainMenu()
{
	floorPtr->Tick(projectSettingsPtr->GetDeltaTime(), false);

	if (isGameOver)
	{
		//Reset Anything from the previously played game. 
		pipesPtr->Reset(); 
		playerPtr->Reset(); 
		scoreManagerPtr->Reset(); 
		isGameOver = false; 
	}
}

//-------------------- GamePlay -------------------- 
void Game::GamePlay()
{
	pipesPtr->Tick(projectSettingsPtr->GetDeltaTime(), false);
	floorPtr->Tick(projectSettingsPtr->GetDeltaTime(), false);
	playerPtr->Tick(projectSettingsPtr->GetDeltaTime(), false);

	ScoreCollisionChecks();

	if (GameOverCollisionChecks())
	{
		isGameOver = true; 
		scoreManagerPtr->GameOver(); 
		sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME_OVER); 
	}
	
}

//-------------------- Game Paused -------------------- 
void Game::GamePaused()
{
	pipesPtr->Tick(projectSettingsPtr->GetDeltaTime(), true);
	floorPtr->Tick(projectSettingsPtr->GetDeltaTime(), true);
	playerPtr->Tick(projectSettingsPtr->GetDeltaTime(), true);
}

//-------------------- Game Over -------------------- 
void Game::GameOver()
{
	pipesPtr->Tick(projectSettingsPtr->GetDeltaTime(), true);
	floorPtr->Tick(projectSettingsPtr->GetDeltaTime(), true);
	playerPtr->Tick(projectSettingsPtr->GetDeltaTime(), true);
}

//-------------------- Game Over Collision Checks -------------------- 
bool Game::GameOverCollisionChecks()
{
	if (CheckCollisionRecs(playerPtr->GetCollisionRectangle(), pipesPtr->GetPipeCollisionRec(Pipes::TOP_PIPE_SET_ONE)))
	{
		playerPtr->PlayerPlayerCrashSound(1);
		return true; 
	}

	if (CheckCollisionRecs(playerPtr->GetCollisionRectangle(), pipesPtr->GetPipeCollisionRec(Pipes::BOTTOM_PIPE_SET_ONE)))
	{
		playerPtr->PlayerPlayerCrashSound(1);
		return true;
	}

	if (CheckCollisionRecs(playerPtr->GetCollisionRectangle(), pipesPtr->GetPipeCollisionRec(Pipes::TOP_PIPE_SET_TWO)))
	{
		playerPtr->PlayerPlayerCrashSound(1);
		return true;
	}

	if (CheckCollisionRecs(playerPtr->GetCollisionRectangle(), pipesPtr->GetPipeCollisionRec(Pipes::BOTTOM_PIPE_SET_TWO)))
	{
		playerPtr->PlayerPlayerCrashSound(1);
		return true;
	}

	if (CheckCollisionRecs(playerPtr->GetCollisionRectangle(), floorPtr->GetCollisionRectangle()))
	{
		playerPtr->PlayerPlayerCrashSound(2);
		return true;
	}

	return false; 
}

//-------------------- Score Collision Checks -------------------- 
void Game::ScoreCollisionChecks()
{
	if (CheckCollisionRecs(playerPtr->GetCollisionRectangle(), pipesPtr->GetPipeScoreCollisionRec(Pipes::PIPE_SET_ONE))
		&& !pipesPtr->GetHasPipeScoreBeenAdded(Pipes::PIPE_SET_ONE))
	{
		pipesPtr->SetHasPipeScoreBeenAdded(Pipes::PIPE_SET_ONE, true);
		scoreManagerPtr->AddToScore(1); 
	}

	if (CheckCollisionRecs(playerPtr->GetCollisionRectangle(), pipesPtr->GetPipeScoreCollisionRec(Pipes::PIPE_SET_TWO))
		&& !pipesPtr->GetHasPipeScoreBeenAdded(Pipes::PIPE_SET_TWO))
	{
		pipesPtr->SetHasPipeScoreBeenAdded(Pipes::PIPE_SET_TWO, true);
		scoreManagerPtr->AddToScore(1);
	}
}

