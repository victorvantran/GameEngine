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
	// Camera
	glm::vec3 _cameraPos = glm::vec3( 0.0f, 0.0f, 3.0f );
	glm::vec3 _cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
	glm::vec3 _cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );
	glm::vec3 _cameraRight = glm::vec3( 1.0f, 0.0f, 0.0f );
	float _yaw = -90.0f;
	float _pitch = 0.0f;

	float _lastMouseX = 1920.0f / 2.0f;
	float _lastMouseY = 1080.0f / 2.0f;


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
	 * To be called every time the mouse is moved. Perform subsequent tasks.
	 *
	 * Update the camera.
	 *
	 * @param width an int of the current working area width
	 * @param height an int of the current the working area height
	 * @return void
	 */
	void resize_window_callback( int width, int height );


	/**
	 * To be called every time the mouse is moved. Perform subsequent tasks.
	 *
	 * Update the camera's direction.
	 *
	 * @param x a double of the current mouse x-coordinate
	 * @param x a double of the current mouse y-coordinate
	 * @return void
	 */
	void mouse_callback( double x, double y );

};


#endif