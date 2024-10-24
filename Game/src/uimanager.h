#pragma once
#include <memory>
#include "raylib.h"

class Button;
class SceneManager; 
class ScoreManager; 

class UIManager
{
public: 
	UIManager(int sWidth, int sHeight, float uiScale, std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<ScoreManager> scoreManager);
    ~UIManager(); 
    void Tick(float dt); 
private: 

    void DisplayButtons(); 
    void DisplayGameTitleUI(); 
    void DisplayScoreUI(); 
    void DisplayGameOverUI(); 

    //SceneManager
    std::shared_ptr<SceneManager> sceneManagerPtr{};

    //ScoreManager
    std::shared_ptr<ScoreManager> scoreManagerPtr{};

    //Screen Size
    int screenHeight{};
    int screenWidth{};

    //Delta Time
    float deltaTime{}; 

    //UI Scale
    float uiAssetsScale{};

    //Main Menu
    Texture2D gameTitleImage{ LoadTexture("res/images/hog-title.png") }; //Game Title
    Texture2D playerCharacterImage{ LoadTexture("res/images/hog.png") }; //Player Character Image
    Vector2 gameTitlePos{}; 
    Vector2 characterImagePos{}; 
    float timeBeforeShowingMenuUI{ 1.5f }; 
    float currentTimeBeforeShowingMenuUI{ 0.0f }; 

    //Game Over
    Texture2D gameOverImage{ LoadTexture("res/images/game-over.png") }; //Game Over Title
    Vector2 gameOverTitlePos{}; 
    Texture2D gameOverPanelNoMedal{ LoadTexture("res/images/game-over-panel.png") };
    Texture2D gameOverPanelBronze{ LoadTexture("res/images/game-over-panel-bronze.png") };
    Texture2D gameOverPanelSilver{ LoadTexture("res/images/game-over-panel-silver.png") };
    Texture2D gameOverPanelGold{ LoadTexture("res/images/game-over-panel-gold.png") };
    Vector2 gameOverPanelPos{}; 
    Vector2 gameOverPanelCurrentGameScorePos{}; 
    Vector2 gameOverPanelBestGameScorePos{}; 
    float timeBeforeShowingGameOverUI{ 1.5f }; 
    float currentTimeBeforeShowingGameOverUI{ 0.0f };

    //Game Score
    Vector2 gameScorePositon{}; 

    //Buttons
    std::shared_ptr<Button> mainMenuPlayButtonPtr{}; // Main Menu Play
    std::shared_ptr<Button> gamePauseButtonPtr{}; //Game Pause Button
    std::shared_ptr<Button> unPauseGameButtonPtr{};//Unpause Game Button
    std::shared_ptr<Button> restartGameButtonPtr{}; //Game Over Restart Button
};