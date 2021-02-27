#include "Game.h"


Game::Game() : _gameTime(), _renderManager(), _camera(),
_windowWidth( 800 ), _windowHeight( 640 ), _windowTitle( "untitled" ) {}


Game::Game( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) : _gameTime(), _renderManager(), _camera(),
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
	float deltaTime = this->_gameTime.getDeltaTime();

	// Process Mouse
	// Mouse Movement
	double mouseX, mouseY;
	glfwGetCursorPos( window, &mouseX, &mouseY );
	float xOffset = mouseX - this->_prevMouseX;
	float yOffset = mouseY - this->_prevMouseY;
	this->_prevMouseX = mouseX;
	this->_prevMouseY = mouseY;
	if ( xOffset != 0.0f || yOffset != 0.0f )
	{
		this->_camera.processTiltInput( xOffset, -yOffset );
	}

	// Mouse Scroll
	//this->_camera.processZoom( 0.0f * deltaTime );


	// Process Keys
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, true );
	}

	if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
	{
		this->_camera.processPanInput( Camera::PanDirection::FORWARD, deltaTime );
	}
	if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
	{
		this->_camera.processPanInput( Camera::PanDirection::BACKWARD, deltaTime );
	}

	if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
	{
		this->_camera.processPanInput( Camera::PanDirection::LEFT, deltaTime );

	}
	if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
	{
		this->_camera.processPanInput( Camera::PanDirection::RIGHT, deltaTime );
	}

	if ( glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS )
	{
		this->_camera.processPanInput( Camera::PanDirection::UP, deltaTime );

	}
	if ( glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS )
	{
		this->_camera.processPanInput( Camera::PanDirection::DOWN, deltaTime );

	}




}


