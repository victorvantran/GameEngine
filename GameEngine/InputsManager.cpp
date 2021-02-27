#include "InputsManager.h"
#include "RenderManager.h"


void InputsManager::mouse_callback( GLFWwindow* window, GLdouble x, GLdouble y )
{
	RenderManager* renderManager = reinterpret_cast< RenderManager* >( glfwGetWindowUserPointer( window ) );
	renderManager->mouse_callback( x, y );
	return;
}


void InputsManager::resize_window_callback( GLFWwindow* window, GLint x, GLint y )
{
	RenderManager* renderManager = reinterpret_cast< RenderManager* >( glfwGetWindowUserPointer( window ) );
	renderManager->resize_window_callback( x, y );
	return;
}


static void keyfun_callback( GLFWwindow* window, GLint key, GLint scanCode, GLint action, GLint mods )
{
	RenderManager* renderManager = reinterpret_cast< RenderManager* >( glfwGetWindowUserPointer( window ) );
	renderManager->keyfun_callback( key, scanCode, action, mods );
}