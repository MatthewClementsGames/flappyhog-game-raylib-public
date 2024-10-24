#pragma once
#include <memory>
#include "raylib.h"

class SceneManager
{
public:
	SceneManager(int screenWidth, int screenHeight, float bScaleSize, float rScaleSize);
	~SceneManager();

	void Tick(float dt);

    enum scene {
        SCENE_RAYLIB_SPLASH_SCREEN,
        SCENE_MC_SPLASH_SCREEN,
        SCENE_MAIN_MENU,
        SCENE_GAME,
        SCENE_PAUSE,
        SCENE_GAME_OVER
    };

    void SwitchScene(scene newScene);
private: 
    scene currentScene{};

    void DrawRaylibSplashScreen();
    void DrawMCSplashScreenScene();
    void DrawMainMenuScene();
    void DrawGameScene();
    void DrawPauseScene();
    void DrawGameOverScene();

    int screenWidth{}; 
    int screenHeight{}; 

    float backgroundScaleSize{};
    float raylibIconScaleSize{};

    float deltaTime{};

    //Raylib Splash Screen
    Texture2D raylibSplashScreenIcon{ LoadTexture("res/images/raylibICON.png") }; 
    float raylibSplashScreenActiveTime{ 3.0f };

    //Matthew Clements Games Splash Screen 
    Texture2D mcGamesSplashScreen{ LoadTexture("res/images/matthewclementsgamessplashscreen.png") };
    float mcSplashScreenActiveTime{ 3.0f };

    //Background Image
    void DrawBackgroundAndMove(bool isGamePaused);
    Texture2D backgroundImage{ LoadTexture("res/images/background.png") };
    float backgroundX{ 0.0f };
    float backgroundScrollingSpeed{-50.0f};

    //Game Music
    Music gameMusic{ LoadMusicStream("res/audio/game-music.mp3") }; 
    bool hasGameMusicBeenStarted{ false }; 
    bool isGameMusicPlaying{ false }; 
    void PlayMusic(bool _playMusic); 

public: 
    scene GetCurrentScene() const { return currentScene; }; 
};
