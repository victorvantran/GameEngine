#include "Game.h"


Game::Game() : _gameTime(), _openGLManager(), _camera(),
_windowWidth( 800 ), _windowHeight( 640 ), _windowTitle( "untitled" ) {}


Game::Game( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) : _gameTime(), _openGLManager(), _camera(),
_windowWidth( windowWidth ), _windowHeight( windowHeight ), _windowTitle( windowTitle ) {}


Game::~Game() {}


void Game::run()
{
	this->initialize();

	this->_openGLManager.createWindow( this->_windowWidth, this->_windowHeight, this->_windowTitle );

	this->loadContent();

	while ( !glfwWindowShouldClose( this->_openGLManager.getWindow() ) )
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

	this->_openGLManager.destroyWindow();
}


void Game::processInput( GLFWwindow* window )
{
	float deltaTime = this->_gameTime.getDeltaTime();


	// Close Window
	if ( Keyboard::getKey( GLFW_KEY_ESCAPE ) )
	{
		glfwSetWindowShouldClose( window, true );
	}


	// Camera
	this->_camera.processTiltInput( Mouse::getDeltaX(), Mouse::getDeltaY() );
	this->_camera.processZoom( Mouse::getScrollDeltaY() );
	if ( Keyboard::getKey( GLFW_KEY_W ) )
	{
		this->_camera.processPanInput( Camera::PanDirection::FORWARD, deltaTime );
	}
	if ( Keyboard::getKey( GLFW_KEY_S ) )
	{
		this->_camera.processPanInput( Camera::PanDirection::BACKWARD, deltaTime );
	}
	if ( Keyboard::getKey( GLFW_KEY_A ) )
	{
		this->_camera.processPanInput( Camera::PanDirection::LEFT, deltaTime );
	}
	if ( Keyboard::getKey( GLFW_KEY_D ) )
	{
		this->_camera.processPanInput( Camera::PanDirection::RIGHT, deltaTime );
	}
	if ( Keyboard::getKey( GLFW_KEY_Q ) )
	{
		this->_camera.processPanInput( Camera::PanDirection::UP, deltaTime );
	}
	if ( Keyboard::getKey( GLFW_KEY_E ) )
	{
		this->_camera.processPanInput( Camera::PanDirection::DOWN, deltaTime );
	}


	return;
}


