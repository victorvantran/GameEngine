#include "Game.h"


Game::Game() : _gameTime(), _renderManager(),
_windowWidth( 800 ), _windowHeight( 640 ), _windowTitle( "untitled" ) {}


Game::Game( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) : _gameTime(), _renderManager(),
_windowWidth( windowWidth ), _windowHeight( windowHeight ), _windowTitle( windowTitle ) {}


Game::~Game() {}


void Game::run()
{
	this->initialize();

	this->_renderManager.createWindow( this->_windowWidth, this->_windowHeight, this->_windowTitle );

	this->loadContent();

	while ( !glfwWindowShouldClose( this->_renderManager.getWindow() ) )
	{
		// Update time
		this->_gameTime.setDeltaTime( ( float )( glfwGetTime() - this->_gameTime.getTotalElapsedSeconds() ) );
		this->_gameTime.setTotalElapsedSeconds( glfwGetTime() );

		std::cout << ( int )( 1.0 / this->_gameTime.getDeltaTime() ) << std::endl;

		// Update game logic
		this->update();

		glfwPollEvents();

		this->render();
	}

	this->_renderManager.destroyWindow();
}


void Game::processInput( GLFWwindow* window )
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, true );
	}

	const float cameraSpeed = 2.5f * this->_gameTime.getDeltaTime();
	if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
		this->_renderManager._cameraPos += glm::normalize( this->_renderManager._cameraFront ) * cameraSpeed;
	if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
		this->_renderManager._cameraPos -= glm::normalize( this->_renderManager._cameraFront ) * cameraSpeed;
	if ( glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS )
		this->_renderManager._cameraPos += this->_renderManager._cameraUp * cameraSpeed;
	if ( glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS )
		this->_renderManager._cameraPos -= this->_renderManager._cameraUp * cameraSpeed;
	if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
		this->_renderManager._cameraPos -= glm::normalize( glm::cross( this->_renderManager._cameraFront, this->_renderManager._cameraUp ) ) * cameraSpeed;
	if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
		this->_renderManager._cameraPos += glm::normalize( glm::cross( this->_renderManager._cameraFront, this->_renderManager._cameraUp ) ) * cameraSpeed;
}


