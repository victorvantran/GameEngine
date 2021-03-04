#include "OpenGLManager.h"


///
OpenGLManager::OpenGLManager()
{
}


OpenGLManager::~OpenGLManager()
{
	this->destroyWindow();
}


void OpenGLManager::createWindow( std::uint16_t width, std::uint16_t height, const std::string& title,
	bool resizable, bool vSynch )
{
	// Initialize the framework with the correct version (3.3) and using CORE_PROFILE mode
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

	glfwWindowHint( GLFW_RESIZABLE, resizable );
	glfwWindowHint( GLFW_FOCUSED, true );

	// Create a window object
	this->_window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
	if ( this->_window == NULL )
	{
		std::cout << "Failed to create GLFWWindow" << std::endl;
		glfwTerminate();
	}

	// Tell GLFW to make the context of the window the main context on the current thread
	glfwMakeContextCurrent( this->_window );

	// Initalize GLAD to have more compatibiltiy in our framework
	if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
	}

	// Tell OpenGL the size of the RenderingWindow
	glViewport( 0, 0, width, height );

	// Initial Window Work Area
	// Set window to be in the center of the monitor
	int workAreaXPos;
	int workAreaYPos;
	int workAreaWidth;
	int workAreaHeight;
	glfwGetMonitorWorkarea( glfwGetPrimaryMonitor(), &workAreaXPos, &workAreaYPos, &workAreaWidth, &workAreaHeight );
	int midPosX = ( workAreaWidth - width ) / 2;
	int midPosY = ( workAreaHeight - height ) / 2;
	glfwSetWindowPos( this->_window, midPosX, midPosY );

	// Vsynch toggle
	glfwSwapInterval( vSynch ? 1 : 0 );

	// Z-buffering
	glEnable( GL_DEPTH_TEST );

	// Mouse
	glfwSetInputMode( this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	// Callback Handling
	glfwSetWindowUserPointer( this->_window, reinterpret_cast< void* >( this ) );

	glfwSetFramebufferSizeCallback( this->_window, OpenGLManager::resize_window_callback );
	glfwSetCursorPosCallback( this->_window, Mouse::cursorPosCallback );
	glfwSetMouseButtonCallback( this->_window, Mouse::mouseButtonCallback );
	glfwSetScrollCallback( this->_window, Mouse::scrollCallback );
	glfwSetKeyCallback( this->_window, Keyboard::keyCallback );
	return;
}


void OpenGLManager::destroyWindow()
{
	glfwTerminate();
	return;
}


GLFWwindow* OpenGLManager::getWindow()
{
	return this->_window;
}


void OpenGLManager::resize_window_callback( GLFWwindow* window, GLint width, GLint height )
{
	glViewport( 0, 0, width, height );
	// [!] reupdate Game Screen width and height
	return;
}
