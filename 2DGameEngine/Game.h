#pragma once

#include "GameTime.h"
#include "RenderManager.h"

class Game
{
protected:
	GameTime _gameTime;
	RenderManager _renderManager;

	std::uint16_t _windowWidth;
	std::uint16_t _windowHeight;
	std::string _windowTitle;
public:
	Game() : _gameTime(), _renderManager(),
		_windowWidth( 800 ), _windowHeight( 640 ), _windowTitle( "untitled" ) {}
	Game( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) : _gameTime(), _renderManager(),
		_windowWidth( windowWidth ), _windowHeight( windowHeight ), _windowTitle( windowTitle ) {}
	~Game() {}

	void run()
	{
		this->initialize();

		this->_renderManager.createWindow( this->_windowWidth, this->_windowHeight, this->_windowTitle );

		this->loadContent();

		while ( !glfwWindowShouldClose( this->_renderManager.getWindow() ) )
		{
			// Update time
			this->_gameTime.setDeltaTime( ( float )( glfwGetTime() - this->_gameTime.getTotalElapsedSeconds() ) );
			this->_gameTime.setTotalElapsedSeconds( glfwGetTime() );

			std::cout << 1.0 / this->_gameTime.getDeltaTime() << std::endl;

			// Update game logic
			this->update();

			glfwPollEvents();

			this->render();
		}

		this->_renderManager.destroyWindow();
	}


	virtual void initialize() = 0;
	virtual void loadContent() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

};