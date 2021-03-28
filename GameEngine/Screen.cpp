#include "Screen.h"


std::uint32_t Screen::_width = settings::screen::DEFAULT_WIDTH;
std::uint32_t Screen::_height = settings::screen::DEFAULT_HEIGHT;


void Screen::frameBufferSizeCallback( GLFWwindow* window, GLint width, GLint height )
{
	glViewport( 0, 0, width, height );
	Screen::_width = width;
	Screen::_height = height;
	return;
}



Screen::Screen() 
	: _window( nullptr )
{

}



Screen::~Screen()
{
}



bool Screen::initiate( std::string title, GLboolean fullscreen, GLboolean resizable )
{
	glfwWindowHint( GLFW_RESIZABLE, resizable && !fullscreen );
	glfwWindowHint( GLFW_FOCUSED, true );
	glfwWindowHint( GLFW_SAMPLES, 4 ); // [!]

	// Create a window object
	if ( fullscreen )
	{
		glfwWindowHint( GLFW_DECORATED, NULL );
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode( primaryMonitor );
		Screen::_width = videoMode->width;
		Screen::_height = videoMode->height;
		this->_window = glfwCreateWindow( Screen::_width, Screen::_height, title.c_str(), glfwGetPrimaryMonitor(), NULL );
	}
	else
	{
		this->_window = glfwCreateWindow( Screen::_width, Screen::_height, title.c_str(), NULL, NULL );
	}

	if ( this->_window == NULL )
	{
		std::cout << "Failed to create GLFWWindow" << std::endl;
		return false;
	}

	// Tell GLFW to make the context of the window the main context on the current thread
	glfwMakeContextCurrent( this->_window );

	// Initial Window Work Area
	// Set window to be in the center of the monitor
	int workAreaXPos;
	int workAreaYPos;
	int workAreaWidth;
	int workAreaHeight;
	glfwGetMonitorWorkarea( glfwGetPrimaryMonitor(), &workAreaXPos, &workAreaYPos, &workAreaWidth, &workAreaHeight );
	int midPosX = ( workAreaWidth - Screen::_width ) / 2;
	int midPosY = ( workAreaHeight - Screen::_height ) / 2;
	glfwSetWindowPos( this->_window, midPosX, midPosY );

	return true;
}



void Screen::setAttributes( bool vSynch )
{
	glViewport( 0, 0, Screen::_width, Screen::_height );

	// Vsynch toggle
	glfwSwapInterval( vSynch ? 1 : 0 );

	// Mouse
	glfwSetInputMode( this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	return;
}



void Screen::setCallbacks()
{
	// Window callbacks
	glfwSetFramebufferSizeCallback( this->_window, Screen::frameBufferSizeCallback );

	// Mouse callbacks
	// glfwSetCursorPosCallback( this->_window, Mouse::cursorPosCallback );
	glfwSetMouseButtonCallback( this->_window, Mouse::mouseButtonCallback );
	glfwSetScrollCallback( this->_window, Mouse::scrollCallback );

	// Keyboard callbacks
	glfwSetKeyCallback( this->_window, Keyboard::keyCallback );

	return;
}



void Screen::clear()
{
	//glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	return;
}



void Screen::newFrame()
{
	glfwSwapBuffers( this->_window );
	return;
}



// Getters 
std::uint32_t Screen::getWidth()
{
	return Screen::_width;
}



std::uint32_t Screen::getHeight()
{
	return Screen::_height;
}



GLFWwindow* Screen::getWindow()
{
	return this->_window;
}



bool Screen::getShouldClose() const
{
	return glfwWindowShouldClose( this->_window );
}



// Setters
void Screen::setShouldClose( bool shouldClose )
{
	glfwSetWindowShouldClose( this->_window, shouldClose );
	return;
}