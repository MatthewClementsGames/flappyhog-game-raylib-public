#pragma once
#include "raylib.h"

class ProjectSettings
{
public:
    ProjectSettings() {};

    int GetScreenWidth() const { return screenWidth; };
    int GetScreenHeight() const { return screenHeight; };

    float GetBackgroundScaleSize() const { return backgroundScaleSize; };
    float GetAssetsScaleSize() const { return assetsScaleSize; };
    float GetUIAssetsScaleSize() const { return uiAssetsScaleSize;  }
    float GetRaylibIconScaleSize() const { return raylibIconScaleSize; };

    float GetDeltaTime() { return GetFrameTime(); };

private:

    const int screenWidth{ 540 };
    const int screenHeight{ 960 };

    const float backgroundScaleSize{ 1.0f };
    const float assetsScaleSize{ 1.0f };
    const float uiAssetsScaleSize{ 1.0f }; 
    const float raylibIconScaleSize{ 1.0f };
    
};