#ifndef SCREEN_H
#define SCREEN_H

#include <cstdint>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/io/Mouse.h"
#include "src/io/Keyboard.h"

#include "Settings.h"

class Screen
{
private:
	static std::uint32_t _width;
	static std::uint32_t _height;

	GLFWwindow* _window;

private:
	/**
	 * Relays
	 *
	 * Finds the pointer to the Game object that owns the window.
	 * Updates viewport
	 *
	 * @return void
	 */
	static void frameBufferSizeCallback( GLFWwindow* window, GLint width, GLint height );
public:
	Screen();
	~Screen();


	/**
	 * Create the GLFWwindow object
	 *
	 * @parameter title a string for the title of the window
	 * @parameter resizable a boolean toggle for working area resizability
	 * @return void
	 */
	bool initiate( std::string title = "untitled", GLboolean fullscreen = GL_TRUE, GLboolean resizable = GL_FALSE );


	/**
	 * Set the attributes of the window before rendering can begin
	 *
	 * Attributes: viewport, vSynch, etc.
	 *
	 * @parmeter vSynch a boolean toggle for double buffering on or off
	 * @return void
	 */
	void setAttributes( bool vSynch = GL_TRUE );


	/**
	 * Set the framebuffersize and io callbacks
	 *
	 * @return void
	 */
	void setCallbacks();



	/**
	 * Clears the screen
	 *
	 * Clears both color and z buffers
	 * Clears both color and z buffers
	 *
	 * @return void
	 */
	void clear();



	/**
	 * Swaps buffers
	 *
	 * @return void
	 */
	void newFrame();


	/// Getters 
	static std::uint32_t getWidth();
	static std::uint32_t getHeight();


	/**
	 * Returns a pointer to the GLFWwindow
	 *
	 * @return GLFWwindow* a pointer to the window
	 */
	GLFWwindow* getWindow();

	bool getShouldClose() const;
	

	/// Setters
	void setShouldClose( bool shouldClose );
};

#endif
