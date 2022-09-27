#include "MainGame.h"

MainGame::MainGame()
{
	m_ScreenWidth = 1024;
	m_ScreenHeight = 768;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{	
	if (!initSystems())
	{
		SDL_Log("initSystems failed.");
		SDL_Quit();
		return;
	}

	gameLoop();	
}

bool MainGame::initSystems()
{
	SDL_Log("initSystems...");

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// create window
	m_Window = SDL_CreateWindow("Graphics Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_OPENGL);
	if (m_Window == nullptr)
	{
		SDL_Log("Failed to create window.");
		return false;
	}

	// create OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);
	if (glContext == nullptr)
	{
		SDL_Log("Failed to create SDL_GLContext.");
		return false;
	}

	// initialize GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		SDL_Log("Failed to initialize glew");
		return false;
	}

	// setup double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.f, 0.f, 0.f, 1.f);

	SDL_Log("initSystems...done");

	return true;
}

void MainGame::gameLoop()
{
	while (m_GameState != GameState::EXIT)
	{
		processInput();
		render();
	}
}

void MainGame::processInput()
{
	SDL_Event evt;
	while(SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			m_GameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			
			break;
		}
	}
}

void MainGame::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// immediate mode - bad
	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(0.3f, 0.8f, 0.1f);
	glVertex2f(0.f, 0.f);	
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);	
	glEnd();

	SDL_GL_SwapWindow(m_Window);
}
