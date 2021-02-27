#include "InputsManager.h"
#include "RenderManager.h"


void InputsManager::mouse_callback( GLFWwindow* window, double x, double y )
{
	RenderManager* renderManager = reinterpret_cast< RenderManager* >( glfwGetWindowUserPointer( window ) );
	renderManager->mouse_callback( x, y );
	return;
}


void InputsManager::resize_window_callback( GLFWwindow* window, int x, int y )
{
	RenderManager* renderManager = reinterpret_cast< RenderManager* >( glfwGetWindowUserPointer( window ) );
	renderManager->resize_window_callback( x, y );
	return;
}