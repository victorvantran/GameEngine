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



class InputsManager;


class RenderManager
{
private:
	GLFWwindow* _window;
public:
public:
	RenderManager();
	~RenderManager();
	
	
	/**
	 * Create the GLFWwindow
	 *
	 * @parameter width an unsigned 16-bit integer to establish window width
	 * @parameter height an unsigned 16-bit integer to establish window height
	 * @parameter title a constant string reference to title the window
	 * @parameter resizable a boolean toggle for working area resizability
	 * @parmeter vSynch a boolean toggle for double buffering on or off
	 * @return void
	 */
	void createWindow( std::uint16_t width = 800, std::uint16_t height = 640, const std::string& title = "untitled", bool resizable = true, bool vSynch = false );


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
	 * To be called every time the mouse is moved. Perform subsequent tasks.
	 *
	 * Update the camera.
	 *
	 * @param width an int of the current working area width
	 * @param height an int of the current the working area height
	 * @return void
	 */
	void resize_window_callback( GLint width, GLint height );


	/**
	 * To be called every time the mouse is moved. Perform subsequent tasks.
	 *
	 * Update the camera's direction.
	 *
	 * @param x a double of the current mouse x-coordinate
	 * @param x a double of the current mouse y-coordinate
	 * @return void
	 */
	void mouse_callback( GLdouble x, GLdouble y );


	/**
	 * To be called every time a key is pressed. Perform subsequent tasks.
	 *
	 * @param key an integer to represent the key pressed
	 * @param scancode platform-specific scancode
	 * @param action specific action on key
	 * @param mods
	 * @return void
	 */
	void keyfun_callback( GLint key, GLint scancode, GLint action, GLint mods );

};


#endif