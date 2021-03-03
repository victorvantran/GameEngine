#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard
{
private:
    static bool _keys[];
    static bool _keysToggled[];


public:
    // Callbacks

    /**
     * To be called every time a key is pressed. Perform subsequent tasks.
     *
     * @param key an integer to represent the key pressed
     * @param scancode platform-specific scancode
     * @param action specific action on key
     * @param mods
     * @return void
     */
    static void keyCallback( GLFWwindow* window, std::int32_t key, std::int32_t scanCode, std::int32_t action, std::int32_t mods );



    // Getters

    /**
     *
     *
     * @return bool
     */
    static bool getKey( std::int32_t key );




    /**
     *
     *
     * @return bool
     */
    static bool getKeyToggled( std::int32_t key );





    /**
     *
     *
     * @return bool
     */
    static bool getKeyToggledUp( std::int32_t key );


    /**
     * 
     *
     * @return bool
     */
    static bool getKeyToggledDown( std::int32_t key );
};


#endif