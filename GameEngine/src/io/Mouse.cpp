#include "Mouse.h"

double Mouse::_x = 0.0;
double Mouse::_y = 0.0;
double Mouse::_prevX = 0.0;
double Mouse::_prevY = 0.0;

double Mouse::_deltaX = 0.0;
double Mouse::_deltaY = 0.0;

double Mouse::_scrollDeltaX = 0.0;
double Mouse::_scrollDeltaY = 0.0;

bool Mouse::_initialMouse = true;


bool Mouse::_buttons[GLFW_MOUSE_BUTTON_LAST] = { false };

bool Mouse::_buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { false };

// Set the initial/prev mouse positions to be the same. Update the current and prev mouse positions and the delta movement
 void Mouse::cursorPosCallback( GLFWwindow* window, double x, double y )
{
     Mouse::_x = x;
     Mouse::_y = y;

     if ( Mouse::_initialMouse )
     {
         Mouse::_prevX = x;
         Mouse::_prevY = y;

         Mouse::_initialMouse = false;
     }

     Mouse::_deltaX = x - Mouse::_prevX;
     Mouse::_deltaY = Mouse::_prevY - y;

     Mouse::_prevX = x;
     Mouse::_prevY = y;
     return;
}


 void Mouse::mouseButtonCallback( GLFWwindow* window, std::int32_t button, std::int32_t action, std::int32_t mods )
{
     if ( action != GLFW_RELEASE )
     {
         if ( !Mouse::_buttons[button] )
         {
             Mouse::_buttons[button] = true;
         }
     }
     else
     {
         Mouse::_buttons[button] = false;
     }

     Mouse::_buttonsChanged[button] = action != GLFW_REPEAT;

     return;
}


 void Mouse::scrollCallback( GLFWwindow* window, double offsetX, double offsetY )
{
     Mouse::_scrollDeltaX = offsetX;
     Mouse::_scrollDeltaY = offsetY;

     return;
}


double Mouse::getMouseX()
{
     return Mouse::_x;
}


double Mouse::getMouseY()
{
     return Mouse::_y;
}


double Mouse::getDeltaX()
{
    double deltaX = Mouse::_deltaX;
    Mouse::_deltaX = 0.0;
    return deltaX;
}


double Mouse::getDeltaY()
{
    double deltaY = Mouse::_deltaY;
    Mouse::_deltaY = 0.0;
    return deltaY;
}


double Mouse::getScrollDeltaX()
{
    double scrollDeltaX = Mouse::_scrollDeltaX;
    Mouse::_scrollDeltaX = 0.0;
    return scrollDeltaX;
}


double Mouse::getScrollDeltaY()
{
    double scrollDeltaY = Mouse::_scrollDeltaY;
    Mouse::_scrollDeltaY = 0.0;
    return scrollDeltaY;
}


bool Mouse::getButton( int button )
{
    return Mouse::_buttons[button];
}


bool Mouse::getButtonChanged( int button )
{
    bool changed = Mouse::_buttonsChanged[button];
    Mouse::_buttonsChanged[button] = false;
    return changed;
}


bool Mouse::getButtonUp( int button )
{
    return !Mouse::_buttons[button] && Mouse::getButtonChanged( button );
}


bool Mouse::getButtonDown( int button )
{
    return Mouse::_buttons[button] && Mouse::getButtonChanged( button );
}