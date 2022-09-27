#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#undef main
#include <GL/glew.h>

enum class GameState 
{
	PLAY,
	EXIT
};


class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	
private:
	bool initSystems();
	
	void gameLoop();

	void processInput();

	void render();

private:
	SDL_Window* m_Window{ nullptr };
	int m_ScreenWidth{ 0 };
	int m_ScreenHeight{ 0 };
	GameState m_GameState{ GameState::PLAY };
};

