#ifndef GAME_H
#define GAME_H
#include <SDL.h>

class Game {
public:
    Game();
    ~Game() = default;
    void Init();
    void Input();
    void Update();
    void UpdateGrapics();
    void End();

private:
    void Run();

    bool isRunning = true;

};

#endif //GAME_H
