#include "Game.h"


Game::Game()
{

}

void Game::Init()
{

}

void Game::Run()
{
    while (isRunning)
    {
        Input();
        Update();
        UpdateGrapics();
    }
}

void Game::Input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            isRunning = false;
            break;
        }

        if(e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {

            }
        }
    }
}

void Game::Update()
{

}

void Game::UpdateGrapics()
{

}

void Game::End()
{

}


