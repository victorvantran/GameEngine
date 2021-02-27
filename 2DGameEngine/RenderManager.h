#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <iostream>

class RenderManager
{
private:
	GLFWwindow* _window;



public:
	// Camera
	glm::vec3 _cameraPos = glm::vec3( 0.0f, 0.0f, 3.0f );
	glm::vec3 _cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
	glm::vec3 _cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );
	glm::vec3 _cameraRight = glm::vec3( 1.0f, 0.0f, 0.0f );
	float _yaw = -90.0f;
	float _pitch = 0.0f;

	float _lastMouseX = 1920.0f / 2.0f;
	float _lastMouseY = 1080.0f / 2.0f;
private:
	void framebuffer_size_callback( GLFWwindow* window, int width, int height )
	{
		// Resize the render window
		glViewport( 0, 0, width, height );
		return;
	}


	static void mouse_callbacks( GLFWwindow* window, double xpos, double ypos )
	{
		return;
	}




	static void s_mouse_callback( GLFWwindow* window, double x, double y )
	{
		RenderManager* renderManager = reinterpret_cast< RenderManager* >( glfwGetWindowUserPointer( window ) );
		renderManager->mouse_callback( x, y );
	
		return;
	}


	void mouse_callback( double x, double y )
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

public:
	RenderManager()
	{
	}


	~RenderManager()
	{
		this->destroyWindow();
	}


	void createWindow( std::uint16_t width = 800, std::uint16_t height = 640, const std::string& title = "untitled",
		bool resizable = true, bool vSynch = true )
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

		glfwMakeContextCurrent( this->_window ); // Tell GLFW to make the context of the window the main context on the current thread

		// Initalize GLAD to have more compatibiltiy in our framework
		if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			glfwTerminate();
		}

		// Tell OpenGL the size of the RenderingWindow
		glViewport( 0, 0, width, height );

		// Resize the render window every time the window is resized 
		auto resiseWindowCallback = [] ( GLFWwindow* window, int w, int h ) { static_cast< RenderManager* >( glfwGetWindowUserPointer( window ) )->framebuffer_size_callback( window, w, h ); };
		glfwSetFramebufferSizeCallback( this->_window, resiseWindowCallback );


		// Set window to be in the ceneter of the monitor
		int workAreaXPos;
		int workAreaYPos;
		int workAreaWidth;
		int workAreaHeight;
		glfwGetMonitorWorkarea( glfwGetPrimaryMonitor(), &workAreaXPos, &workAreaYPos, &workAreaWidth, &workAreaHeight );
		int midPosX = ( workAreaWidth - width ) / 2;
		int midPosY = ( workAreaHeight - height ) / 2;
		glfwSetWindowPos( this->_window, midPosX, midPosY );


		glfwSwapInterval( vSynch ? 1 : 0 ); // Vsynch toggle



		glEnable( GL_DEPTH_TEST ); // Z-buffering




		glfwSetInputMode( this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED ); // Capture cursor
		// Call the mouse callback function every time we register a mouse movement
		/*
		auto mouseCallback = [] ( GLFWwindow* window, double x, double y ) 
		{ 
			static_cast< RenderManager* >( glfwGetWindowUserPointer( window ) )->mouse_callback( x, y ); 
		};
		glfwSetCursorPosCallback( this->_window, mouseCallback );
		*/
		/*
		glfwSetCursorPosCallback( this->_window, [] ( GLFWwindow* window, double x, double y )
		{

		} );
		*/
		//glfwSetCursorPosCallback( this->_window, RenderManager::mouse_callbacks );
		glfwSetWindowUserPointer( this->_window, reinterpret_cast< void* >( this ) );
		glfwSetCursorPosCallback( this->_window, RenderManager::s_mouse_callback );


		this->_lastMouseX = width / 2;
		this->_lastMouseY = height / 2;

		return;
	}


	void destroyWindow()
	{
		glfwTerminate();
		return;
	}


	GLFWwindow* getWindow()
	{
		return this->_window;
	}
};


#endif