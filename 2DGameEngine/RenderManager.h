#pragma once

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

private:
	void framebuffer_size_callback( GLFWwindow* window, int width, int height )
	{
		// Resize the render window
		glViewport( 0, 0, width, height );
		return;
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
		bool resizable = false, bool vSynch = false )
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
		auto func = [] ( GLFWwindow* window, int w, int h ) { static_cast< RenderManager* >( glfwGetWindowUserPointer( window ) )->framebuffer_size_callback( window, w, h ); };
		glfwSetFramebufferSizeCallback( this->_window, func );


		// Set window to be in the ceneter of the monitor
		int workAreaXPos;
		int workAreaYPos;
		int workAreaWidth;
		int workAreaHeight;
		glfwGetMonitorWorkarea( glfwGetPrimaryMonitor(), &workAreaXPos, &workAreaYPos, &workAreaWidth, &workAreaHeight );

		int midPosX = ( workAreaWidth - width ) / 2;
		int midPosY = ( workAreaHeight - height ) / 2;
		glfwSetWindowPos( this->_window, midPosX, midPosY );

		glfwSwapInterval( vSynch ? 1 : 0 );

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