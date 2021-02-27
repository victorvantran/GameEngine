#ifndef INPUTS_MANAGER_H
#define INPUTS_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>



class RenderManger;


class InputsManager
{
private:

public:
	/**
     * Relays the mouse_callback
     *
     * Finds the pointer to the Game object that owns the window.
     * Calls the subsequent method for mouse_callback
     *
     * @return void
     */
	static void mouse_callback( GLFWwindow* window, double x, double y );


    /**
     * Relays the resize_window_callback
     *
     * Finds the pointer to the Game object that owns the window.
     * Calls the subsequent method for resize_window_callback
     *
     * @return void
     */
	static void resize_window_callback( GLFWwindow* window, int x, int y );

};


#endif 