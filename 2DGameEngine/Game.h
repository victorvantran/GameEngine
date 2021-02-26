#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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




	// Camera
	glm::vec3 _cameraPos = glm::vec3( 0.0f, 0.0f, 3.0f );
	glm::vec3 _cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
	glm::vec3 _cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );
	glm::vec3 _cameraRight = glm::vec3( 1.0f, 0.0f, 0.0f );
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

			std::cout << (int )( 1.0 / this->_gameTime.getDeltaTime() ) << std::endl;

			// Update game logic
			this->update();

			glfwPollEvents();

			this->render();
		}

		this->_renderManager.destroyWindow();
	}


	void processInput( GLFWwindow* window )
	{
		if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		{
			glfwSetWindowShouldClose( window, true );
		}


		//std::cout << "y: " << glm::cross( this->_cameraFront, this->_cameraRight ).y << std::endl;
		//std::cout << "x: " << glm::cross( this->_cameraFront, this->_cameraUp ).x << std::endl;

		const float cameraSpeed = 0.05f;
		if ( glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS )
			this->_cameraPos += glm::normalize( this->_cameraFront ) * cameraSpeed;
		if ( glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS )
			this->_cameraPos -= glm::normalize( this->_cameraFront ) * cameraSpeed;
		if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
			this->_cameraPos += glm::normalize( glm::cross( this->_cameraFront, -this->_cameraRight ) ) * cameraSpeed;
		if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
			this->_cameraPos -= glm::normalize( glm::cross( this->_cameraFront, -this->_cameraRight ) ) * cameraSpeed;
		if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
			this->_cameraPos -= glm::normalize( glm::cross( this->_cameraFront, this->_cameraUp ) ) * cameraSpeed;
		if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
			this->_cameraPos += glm::normalize( glm::cross( this->_cameraFront, this->_cameraUp ) ) * cameraSpeed;
	}


	virtual void initialize() = 0;
	virtual void loadContent() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

};


#endif