#include "scenemanager.h"

SceneManager::SceneManager(int psScreenWidth, int psScreenHeight, float bScaleSize, float rScaleSize)
{
    screenWidth = psScreenWidth; 
    screenHeight = psScreenHeight; 

    backgroundScaleSize = bScaleSize; 
    raylibIconScaleSize = rScaleSize; 

    currentScene = SCENE_RAYLIB_SPLASH_SCREEN;
}

SceneManager::~SceneManager()
{
    UnloadTexture(raylibSplashScreenIcon);
    UnloadMusicStream(gameMusic); 
}

//-------------------- Scene Manager Tick -------------------- 
void SceneManager::Tick(float dt)
{
    deltaTime = dt; 

    switch (currentScene)
    {
    case SCENE_RAYLIB_SPLASH_SCREEN:
        DrawRaylibSplashScreen();
        break;
    case SCENE_MC_SPLASH_SCREEN:
        DrawMCSplashScreenScene();
        break;
    case SCENE_MAIN_MENU:
        DrawMainMenuScene();
        break;
    case SCENE_GAME:
        DrawGameScene();
        break;
    case SCENE_PAUSE:
        DrawPauseScene();
        break;
    case SCENE_GAME_OVER:
        DrawGameOverScene();
        break;
    }
}

//-------------------- Switch Scene -------------------- 
void SceneManager::SwitchScene(scene newScene)
{
    currentScene = newScene;
}

//-------------------- Draw Raylib Splash Screen -------------------- 
void SceneManager::DrawRaylibSplashScreen()
{
    ClearBackground(RAYWHITE);
    Vector2 raylibIconPosition{};
    raylibIconPosition.x = ((float)screenWidth / 2.0f) - (((float)raylibSplashScreenIcon.width * raylibIconScaleSize) / 2.0f);
    raylibIconPosition.y = ((float)screenHeight / 2.0f) - (((float)raylibSplashScreenIcon.height * raylibIconScaleSize) / 2.0f);

    DrawTextureEx(raylibSplashScreenIcon, raylibIconPosition, 0.0f, raylibIconScaleSize, WHITE);

    raylibSplashScreenActiveTime -= deltaTime;
    if (raylibSplashScreenActiveTime <= 0.0f)
    {
        SwitchScene(SCENE_MC_SPLASH_SCREEN);
    }
}

//-------------------- Draw Splash Screen -------------------- 
void SceneManager::DrawMCSplashScreenScene()
{
    ClearBackground(BLACK);

    DrawTextureEx(mcGamesSplashScreen, Vector2{ 0.0f,0.0f }, 0.0f, backgroundScaleSize, WHITE); 

    mcSplashScreenActiveTime -= deltaTime;
    if (mcSplashScreenActiveTime <= 0.0f)
    {
        SwitchScene(SCENE_MAIN_MENU);
    }
}

//-------------------- Draw Main Menu -------------------- 
void SceneManager::DrawMainMenuScene()
{
    ClearBackground(WHITE);
    DrawBackgroundAndMove(false); 

    if (!isGameMusicPlaying)
    {
        PlayMusic(true); 
    }

    UpdateMusicStream(gameMusic); 
}

//-------------------- Draw Game Scene -------------------- 
void SceneManager::DrawGameScene()
{
    //Draw Background
    DrawBackgroundAndMove(false); 
    
    if (!isGameMusicPlaying)
    {
        PlayMusic(true);
    }

    UpdateMusicStream(gameMusic);
}

//-------------------- Draw Pause Scene -------------------- 
void SceneManager::DrawPauseScene()
{
    //Draw Background
    DrawBackgroundAndMove(true); 

    if (isGameMusicPlaying)
    {
        PlayMusic(false);
    }
}

//-------------------- Draw Game Over Scene -------------------- 
void SceneManager::DrawGameOverScene()
{
    //Draw Background
    DrawBackgroundAndMove(true);

    if (isGameMusicPlaying)
    {
        PlayMusic(false);
    }
}

//-------------------- Draw Background and Move it -------------------- 
void SceneManager::DrawBackgroundAndMove(bool isGamePaused)
{
    if (!isGamePaused)
    {
        //Background Movement
        backgroundX += backgroundScrollingSpeed * deltaTime;
        if (backgroundX <= -backgroundImage.width)
        {
            backgroundX = 0;
        }
    }

    Vector2 backgroundOnePos{ backgroundX, 0.0f };
    DrawTextureEx(backgroundImage, backgroundOnePos, 0.0f, 1.0f, WHITE);

    Vector2 backgroundTwoPos{ backgroundX + backgroundImage.width, 0.0f };
    DrawTextureEx(backgroundImage, backgroundTwoPos, 0.0f, 1.0f, WHITE);
}

//-------------------- Play Game Music -------------------- 
void SceneManager::PlayMusic(bool _playMusic)
{
    if (_playMusic)
    {
        if (!hasGameMusicBeenStarted)
        {
            PlayMusicStream(gameMusic);
            gameMusic.looping = true;
            hasGameMusicBeenStarted = true; 
        }
        else
        {
            ResumeMusicStream(gameMusic); 
        }
        isGameMusicPlaying = true; 
    }
    else if (!_playMusic)
    {
        PauseMusicStream(gameMusic); 
        isGameMusicPlaying = false; 
    }
}