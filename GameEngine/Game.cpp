#include "Game.h"


Game::Game() :
	_gameTime(), _screen(), _camera() {}



Game::~Game() 
{
	glfwTerminate();
}


void Game::run()
{
	this->initialize();

	this->loadContent();

	while ( !this->_screen.getShouldClose() )
	{
		// Update time
		this->_gameTime.setDeltaTime( ( float )( glfwGetTime() - this->_gameTime.getTotalElapsedSeconds() ) );
		this->_gameTime.setTotalElapsedSeconds( glfwGetTime() );

		std::cout << "FPS: " << ( int )( 1.0 / this->_gameTime.getDeltaTime() ) << std::endl;

		// Check and call events
		//glfwPollEvents(); // glfwWaitEvents();
		//glfwWaitEventsTimeout( 1.0f / 256.0f );
		glfwPollEvents();


		// Update game logic
		this->update();

		// Render
		this->render();
	}

	//this->_openGLManager.destroyWindow();
}




bool Game::initializeGlad()
{
	if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}



bool Game::initializeScreen()
{
	if ( !this->_screen.initiate() )
	{
		std::cout << "Failed to initialize Screen" << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}



void Game::initializeBufferConfigurations()
{
	// Depth Testing
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

	// Stencil Testing
	glEnable( GL_STENCIL_TEST );
	glStencilFunc( GL_NOTEQUAL, 1, 0xFF );
	glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );

	// Blending
	glEnable( GL_BLEND );
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Face Culling
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	// MultiSample
	glEnable( GL_MULTISAMPLE ); // [!]

	return;
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

	if ( !this->initializeScreen() ) return;
	if ( !this->initializeGlad() ) return;

	this->_screen.setAttributes();
	this->_screen.setCallbacks();

	this->initializeBufferConfigurations();
	return;
}



void Game::processInputs()
{
	float deltaTime = this->_gameTime.getDeltaTime();

	// Close Window
	if ( Keyboard::getKey( GLFW_KEY_ESCAPE ) )
	{
		this->_screen.setShouldClose( true );
	}

	// Camera

	/*
	double mouseDeltaX = Mouse::getDeltaX();
	double mouseDeltaY = Mouse::getDeltaY();
	if ( mouseDeltaX != 0.0 || mouseDeltaY != 0.0 )
	{
		this->_camera.processTiltInput( mouseDeltaX, mouseDeltaY );
	}
	*/

	double mouseX, mouseY;
	glfwGetCursorPos( this->_screen.getWindow(), &mouseX, &mouseY );
	float xOffset = mouseX - Mouse::_prevX;
	float yOffset = mouseY - Mouse::_prevY;
	Mouse::_prevX = mouseX;
	Mouse::_prevY = mouseY;
	if ( xOffset != 0.0f || yOffset != 0.0f )
	{
		this->_camera.processTiltInput( xOffset, -yOffset );
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


	if ( Keyboard::getKey( GLFW_KEY_B ) )
	{
		this->_camera.setPosition( glm::vec3( 128.452, 61.5898, 97.1159 ) );

	}

	if ( Keyboard::getKey( GLFW_KEY_SPACE ) )
	{
		// ( 128.452, 61.5898, 97.1159 )

		glm::vec3 pos = this->_camera.getPosition();
		std::cout << "( " << pos.x << ", " << pos.y << ", " << pos.z << " ) " << std::endl;
	}


	return;
}


