#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <cstdint>
#include <iostream>
#include "stb/stb_image.h"

class Texture
{
private:
	GLuint _texture;
public:
	Texture();


	Texture( const char* filepath );


	virtual ~Texture();

	/**
	 * Create a texture given a filepath to an image.
	 *
	 * @return void
	 */
	void load( const char* filepath );


	/**
	 * Activate and bind to a pre-made texture.
	 *
	 * @return void
	 */
	void bind( std::uint8_t unit );
};


#endif

