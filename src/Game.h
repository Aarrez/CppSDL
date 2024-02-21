#ifndef GAME_H
#define GAME_H
#include <SDL.h>

class Game {
public:
    Game() = default;
    ~Game() = default;
    void Init();
    void Update();
    void UpdateGrapics();
    void End();

private:


};

#endif //GAME_H
