#ifndef MOUSE_H
#define MOUSE_H


#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mouse
{
public:
//private:
	static double _x;
	static double _y;
	static double _prevX;
	static double _prevY;

	static double _deltaX;
	static double _deltaY;

	static double _scrollDeltaX;
	static double _scrollDeltaY;

	static bool _initialMouse;


	static bool _buttons[];
	static bool _buttonsChanged[];
public:
	// Callbacks

	/**
	 * Relays
	 *
	 * Finds the pointer to the Game object that owns the window.
	 * Calls the subsequent method for mouse_callback
	 *
	 * @return void
	 */
	static void cursorPosCallback( GLFWwindow* window, double x, double y );


	/**
	 *
	 *
	 * @return void
	 */
	static void mouseButtonCallback( GLFWwindow* window, std::int32_t button, std::int32_t action, std::int32_t mods );


	/**
	 *
	 *
	 * @return void
	 */
	static void scrollCallback( GLFWwindow* window, double offsetX, double offsetY );



	// Getters

	/**
	 *
	 *
	 * @return double
	 */
	static double getMouseX();


	/**
	 *
	 *
	 * @return double
	 */
	static double getMouseY();


	/**
	 *
	 *
	 * @return double
	 */
	static double getDeltaX();


	/**
	 *
	 *
	 * @return double
	 */
	static double getDeltaY();


	/**
	 *
	 *
	 * @return double
	 */
	static double getScrollDeltaX();


	/**
	 *
	 *
	 * @return double
	 */
	static double getScrollDeltaY();


	/**
	 *
	 *
	 * @return bool
	 */
	static bool getButton( int button );


	/**
	 *
	 *
	 * @return bool
	 */
	static bool getButtonChanged( int button );


	/**
	 *
	 *
	 * @return bool
	 */
	static bool getButtonUp( int button );


	/**
	 *
	 *
	 * @return bool
	 */
	static bool getButtonDown( int button );

};


#endif MOUSE_H