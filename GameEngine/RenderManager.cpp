#include "RenderManager.h"
#include "InputsManager.h"


///
RenderManager::RenderManager() 
{
}


RenderManager::~RenderManager()
{
	this->destroyWindow();
}


void RenderManager::createWindow( std::uint16_t width, std::uint16_t height, const std::string& title,
	bool resizable, bool vSynch )
{
	// Initialize the framework with the correct version (3.3) and using CORE_PROFILE mode
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, resizable );
	// glfwWindowHint( GLFW_DOUBLEBUFFER, vSynch );
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
	this->_lastMouseX = width / 2;
	this->_lastMouseY = height / 2;

	// Callback Handling
	glfwSetWindowUserPointer( this->_window, reinterpret_cast< void* >( this ) );
	glfwSetCursorPosCallback( this->_window, InputsManager::mouse_callback );
	glfwSetFramebufferSizeCallback( this->_window, InputsManager::resize_window_callback );

	return;
}


void RenderManager::destroyWindow()
{
	glfwTerminate();
	return;
}


GLFWwindow* RenderManager::getWindow()
{
	return this->_window;
}


void RenderManager::resize_window_callback( int width, int height )
{
	glViewport( 0, 0, width, height );
	return;
}


void RenderManager::mouse_callback( double x, double y )
{
	float xOffset = x - this->_lastMouseX;
	float yOffset = this->_lastMouseY - y;
	this->_lastMouseX = x;
	this->_lastMouseY = y;

	const float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	this->_yaw = glm::mod( this->_yaw + xOffset, 360.0f );

	this->_pitch += yOffset;


	if ( this->_pitch > 89.5f )
		this->_pitch = 89.5f;
	if ( this->_pitch < -89.5f )
		this->_pitch = -89.5f;

	glm::vec3 newFront;
	newFront.x = std::cosf( glm::radians( this->_yaw ) ) * std::cosf( glm::radians( this->_pitch ) );
	newFront.y = std::sinf( glm::radians( this->_pitch ) );
	newFront.z = std::sinf( glm::radians( this->_yaw ) ) * std::cosf( glm::radians( this->_pitch ) );
	this->_cameraFront = glm::normalize( newFront );
}