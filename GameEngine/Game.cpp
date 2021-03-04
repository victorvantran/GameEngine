#include "Game.h"


Game::Game() :
	_gameTime(), _screen(), _camera() {}



Game::~Game() {}


void Game::run()
{
	this->initialize();

	this->loadContent();

	while ( !this->_screen.getShouldClose() )
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

	//this->_openGLManager.destroyWindow();
}


void Game::initialize()
{
	// Initialize the framework with the correct version (3.3) and using CORE_PROFILE mode
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

	if ( !this->_screen.initiate() )
	{
		glfwTerminate();
		return;
	}

	// Initalize GLAD to have more compatibiltiy in our framework
	if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return;
	}

	this->_screen.setAttributes();
	this->_screen.setCallbacks();
	return;
}


void Game::processInput()
{
	float deltaTime = this->_gameTime.getDeltaTime();


	// Close Window
	if ( Keyboard::getKey( GLFW_KEY_ESCAPE ) )
	{
		this->_screen.setShouldClose( true );
	}


	// Camera
	double mouseDeltaX = Mouse::getDeltaX();
	double mouseDeltaY = Mouse::getDeltaY();
	if ( mouseDeltaX != 0.0 || mouseDeltaY != 0.0 )
	{
		this->_camera.processTiltInput( mouseDeltaX, mouseDeltaY );
	}
	double mouseScrollDeltaY = Mouse::getScrollDeltaY();
	if ( mouseScrollDeltaY != 0.0 )
	{
		this->_camera.processZoom( mouseScrollDeltaY );
	}
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


