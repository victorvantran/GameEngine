#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <iostream>

#include "src/io/Mouse.h"
#include "src/io/Keyboard.h"



class OpenGLManager
{
private:
	GLFWwindow* _window;
public:
public:
	OpenGLManager();
	~OpenGLManager();
	
	
	/**
	 * Create the GLFWwindow
	 *
	 * Set proper callback functions for io management
	 *
	 * @parameter width an unsigned 16-bit integer to establish window width
	 * @parameter height an unsigned 16-bit integer to establish window height
	 * @parameter title a constant string reference to title the window
	 * @parameter resizable a boolean toggle for working area resizability
	 * @parmeter vSynch a boolean toggle for double buffering on or off
	 * @return void
	 */
	void createWindow( std::uint16_t width = 800, std::uint16_t height = 640, const std::string& title = "untitled", bool resizable = true, bool vSynch = true );


	/**
	 * Destroy the GLFWwindow by terminating 
	 *
	 * glfw cleans up after itself
	 * @return void
	 */
	void destroyWindow();


	/**
	 * Returns a pointer to the GLFWwindow
	 * 
	 * @return GLFWwindow* a pointer to the window
	 */
	GLFWwindow* getWindow();
public:


	/**
	 * Relays
	 *
	 * Finds the pointer to the Game object that owns the window.
	 * Updates viewport
	 *
	 * @return void
	 */
	static void resize_window_callback( GLFWwindow* window, GLint width, GLint height );


};


#endif