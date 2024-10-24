#include "uimanager.h"
#include "scenemanager.h"
#include "scoremanager.h"
#include "button.h"

UIManager::UIManager(int sWidth, int sHeight, float uiScale, std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<ScoreManager> scoreManager)
{
    //Setup the variables with the parameters
    screenWidth = sWidth; 
    screenHeight = sHeight; 
    uiAssetsScale = uiScale; 
    sceneManagerPtr = sceneManager; 
    scoreManagerPtr = scoreManager; 

    //Main Menu Button
    mainMenuPlayButtonPtr = std::make_shared<Button>(
        "res/images/start-button.png", 
        uiAssetsScale, 
        Vector2{ (float)screenWidth / 2.0f, ((float)screenHeight / 2.0f) + 125.0f }
    );

    //Pause Button
    gamePauseButtonPtr = std::make_shared<Button>("res/images/pause-button.png", uiAssetsScale, Vector2{ 25.0f, 25.0f });

    //UnPause Button
    unPauseGameButtonPtr = std::make_shared<Button>("res/images/unpause-button.png", uiAssetsScale, Vector2{ 25.0f, 25.0f });

    //Restart Button
    restartGameButtonPtr = std::make_shared<Button>(
        "res/images/restart-button.png", 
        uiAssetsScale, 
        Vector2{ (float)screenWidth / 2.0f, ((float)screenHeight / 2.0f) + 150.0f }
    );

    //Set the positions for the Game Title and Character Image
    gameTitlePos = Vector2{ ((float)screenWidth / 2.0f) - (((float)gameTitleImage.width * uiAssetsScale) / 2.0f), 200.0f };
    characterImagePos = Vector2{ ((float)screenWidth / 2.0f) - (((float)playerCharacterImage.width* uiAssetsScale) / 2.0f), 300.0f };

    //Set the position for the player score display. 
    gameScorePositon.x = ((float)screenWidth / 2.0f) - 10.0f;
    gameScorePositon.y = 10.0f; 

    //Set the Position for the Game Over Title
    gameOverTitlePos = Vector2{ ((float)screenWidth / 2.0f) - (((float)gameOverImage.width * uiAssetsScale) / 2.0f), 100.0f };

    //Set the Position for the Game Over Panel
    gameOverPanelPos = Vector2{ ((float)screenWidth / 2.0f) - (((float)gameOverPanelNoMedal.width * uiAssetsScale) / 2.0f), 200.0f};
    
    //Set the position for the current game score. 
    Vector2 middleOfGameOverPanel{};
    middleOfGameOverPanel.x = gameOverPanelPos.x + ((float)gameOverPanelNoMedal.width * uiAssetsScale) / 2.0f; 
    middleOfGameOverPanel.y = gameOverPanelPos.y + ((float)gameOverPanelNoMedal.height * uiAssetsScale) / 2.0f; 
    gameOverPanelCurrentGameScorePos.x = middleOfGameOverPanel.x + 100.0f; 
    gameOverPanelCurrentGameScorePos.y = middleOfGameOverPanel.y - 55.0f; 

    //Set the position for the best game score. 
    gameOverPanelBestGameScorePos.x = middleOfGameOverPanel.x + 100.0f; 
    gameOverPanelBestGameScorePos.y = middleOfGameOverPanel.y + 40.0f; 

    //Set the current timer before showing the game over UI. 
    currentTimeBeforeShowingGameOverUI = timeBeforeShowingGameOverUI; 

    //Set the current timer before showing the menu UI. 
    currentTimeBeforeShowingMenuUI = timeBeforeShowingMenuUI;
}

UIManager::~UIManager() 
{
    UnloadTexture(gameTitleImage); 
    UnloadTexture(playerCharacterImage); 
    UnloadTexture(gameOverImage); 
    UnloadTexture(gameOverPanelNoMedal); 
    UnloadTexture(gameOverPanelBronze);
    UnloadTexture(gameOverPanelSilver);
    UnloadTexture(gameOverPanelGold);
}

//-------------------- Tick -------------------- 
void UIManager::Tick(float dt)
{
    deltaTime = dt; 

    DisplayGameTitleUI();

    DisplayButtons(); 

    DisplayScoreUI(); 
    
    DisplayGameOverUI(); 

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_MAIN_MENU)
    {
        currentTimeBeforeShowingMenuUI -= deltaTime; 
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_GAME_OVER)
    {
        currentTimeBeforeShowingGameOverUI -= deltaTime;
    }
}

//-------------------- Display Buttons -------------------- 
void UIManager::DisplayButtons()
{
    if (sceneManagerPtr == nullptr)
    {
        return; 
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_MAIN_MENU && currentTimeBeforeShowingMenuUI <= 0)
    {
        mainMenuPlayButtonPtr->Tick(); 

        if (mainMenuPlayButtonPtr->IsPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME);
            currentTimeBeforeShowingMenuUI = timeBeforeShowingMenuUI;
            return; 
        }
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_GAME)
    {
        gamePauseButtonPtr->Tick(); 

        if (gamePauseButtonPtr->IsPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_PAUSE);
            return; 
        }
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_PAUSE)
    {
        unPauseGameButtonPtr->Tick();

        if (unPauseGameButtonPtr->IsPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME);
            return; 
        }
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_GAME_OVER && currentTimeBeforeShowingGameOverUI <= 0)
    {
        restartGameButtonPtr->Tick(); 

        if (restartGameButtonPtr->IsPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_MAIN_MENU);
            currentTimeBeforeShowingGameOverUI = timeBeforeShowingGameOverUI;
            return; 
        }
    }
}

//-------------------- Display Game Title UI -------------------- 
void UIManager::DisplayGameTitleUI()
{
    if (sceneManagerPtr == nullptr)
    {
        return;
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_MAIN_MENU && currentTimeBeforeShowingMenuUI <= 0)
    {
        //Draw the game title. 
        DrawTextureEx(gameTitleImage, gameTitlePos, 0.0f, uiAssetsScale, WHITE);

        //Draw the player character. 
        DrawTextureEx(playerCharacterImage, characterImagePos, 0.0f, uiAssetsScale, WHITE); 
    }
}

//-------------------- Display Score UI -------------------- 
void UIManager::DisplayScoreUI()
{
    if (sceneManagerPtr == nullptr)
    {
        return; 
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_GAME ||
        sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_PAUSE)
    {
        if (scoreManagerPtr != nullptr)
        {
            DrawText(TextFormat("%i", scoreManagerPtr->GetPlayerCurrentScore()), (int)gameScorePositon.x, (int)gameScorePositon.y, 50, RED);
        }
    }
}

//-------------------- Display Game Over UI -------------------- 
void UIManager::DisplayGameOverUI()
{

    if (currentTimeBeforeShowingGameOverUI > 0)
    {
        return; 
    }

    if (sceneManagerPtr == nullptr)
    {
        return;
    }

    if (sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_GAME_OVER)
    {
        if (scoreManagerPtr->GetPlayerBestScore() < scoreManagerPtr->GetBronzeMedalScore())
        {
            //Draw the panel with no medal. 
            DrawTextureEx(gameOverPanelNoMedal, gameOverPanelPos, 0.0f, uiAssetsScale, WHITE);
        }

        if (scoreManagerPtr->GetPlayerBestScore() >= scoreManagerPtr->GetBronzeMedalScore() && scoreManagerPtr->GetPlayerBestScore() < scoreManagerPtr->GetSilverMedalScore())
        {
            //Display Bronze Medal. 
            DrawTextureEx(gameOverPanelBronze, gameOverPanelPos, 0.0f, uiAssetsScale, WHITE);
        }

        if (scoreManagerPtr->GetPlayerBestScore() >= scoreManagerPtr->GetSilverMedalScore() && scoreManagerPtr->GetPlayerBestScore() < scoreManagerPtr->GetGoldMedalScore())
        {
            //Display Silver Medal. 
            DrawTextureEx(gameOverPanelSilver, gameOverPanelPos, 0.0f, uiAssetsScale, WHITE);
        }

        if (scoreManagerPtr->GetPlayerBestScore() >= scoreManagerPtr->GetGoldMedalScore())
        {
            //Display Gold Medal 
            DrawTextureEx(gameOverPanelGold, gameOverPanelPos, 0.0f, uiAssetsScale, WHITE);
        }

        //Draw the game over title. 
        DrawTextureEx(gameOverImage, gameOverTitlePos, 0.0f, uiAssetsScale, WHITE);

        //Draw the players current score
        DrawText(TextFormat("%i", scoreManagerPtr->GetPlayerCurrentScore()), (int)gameOverPanelCurrentGameScorePos.x, (int)gameOverPanelCurrentGameScorePos.y, 50, WHITE);

        //Draw the players best score
        DrawText(TextFormat("%i", scoreManagerPtr->GetPlayerBestScore()), (int)gameOverPanelBestGameScorePos.x, (int)gameOverPanelBestGameScorePos.y, 50, WHITE);

    }
}