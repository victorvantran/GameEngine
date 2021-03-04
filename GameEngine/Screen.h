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

	static void frameBufferSizeCallback( GLFWwindow* window, std::int32_t width, std::int32_t height );
public:
	Screen();
	~Screen();

	bool initiate( std::string title = "untitled", bool resizable = false );
	void setAttributes( bool vSynch = false );
	void setCallbacks();

	void clear();
	void newFrame();


	// Getters 
	static std::uint32_t getWidth();
	static std::uint32_t getHeight();

	GLFWwindow* getWindow();

	bool getShouldClose() const;
	

	// Setters
	void setShouldClose( bool shouldClose );

};

#endif
