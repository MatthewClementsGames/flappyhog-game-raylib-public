#include <memory>

class ProjectSettings; 
class SceneManager;
class ScoreManager; 
class Floor; 
class Player; 
class Pipes; 
class Button; 
class UIManager; 

class Game
{
public:
    Game();
private:

    void MainMenu(); 
    void GamePlay(); 
    void GamePaused(); 
    void GameOver(); 
    bool GameOverCollisionChecks(); 
    void ScoreCollisionChecks(); 

    std::shared_ptr<ProjectSettings> projectSettingsPtr{};
    std::shared_ptr<SceneManager> sceneManagerPtr{};
    std::shared_ptr<ScoreManager> scoreManagerPtr{}; 
    std::shared_ptr<UIManager> uiManagerPtr{};

    std::shared_ptr<Floor> floorPtr; 

    std::shared_ptr<Player> playerPtr; 
    std::shared_ptr<Pipes> pipesPtr;

    bool exitGame{ false };

    bool isGameOver{ false }; 
};
