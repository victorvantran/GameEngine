#include "Keyboard.h"


bool Keyboard::_keys[GLFW_KEY_LAST] = { false };
bool Keyboard::_keysToggled[GLFW_KEY_LAST] = { false };


void Keyboard::keyCallback( GLFWwindow* window, std::int32_t key, std::int32_t scanCode, std::int32_t action, std::int32_t mods )
{
	if ( action != GLFW_RELEASE )
	{
		if ( !Keyboard::_keys[key] )
		{
			Keyboard::_keys[key] = true;
		}
	}
	else
	{
		Keyboard::_keys[key] = false;
	}

	Keyboard::_keysToggled[key] = action != GLFW_REPEAT;

	return;
}


bool Keyboard::getKey( std::int32_t key )
{
	return Keyboard::_keys[key];
}


bool Keyboard::getKeyToggled( std::int32_t key )
{
	bool toggled = Keyboard::_keysToggled[key];
	Keyboard::_keysToggled[key] = false;
	return toggled;
}


bool Keyboard::getKeyToggledUp( std::int32_t key )
{
	return !Keyboard::_keys[key] && Keyboard::getKeyToggled( key );
}


bool Keyboard::getKeyToggledDown( std::int32_t key )
{
	return Keyboard::_keys[key] && Keyboard::getKeyToggled( key );
}