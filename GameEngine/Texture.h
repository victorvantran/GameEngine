#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <cassert>
#include <cstdint>
#include <iostream>



#include <assimp/scene.h>

#include "stb/stb_image.h"

#include <string>




struct Texture
{
public:
	std::uint32_t id;
	aiTextureType type;
	std::string directory;
	std::string path;
public:

	Texture( std::string dir, std::string path, aiTextureType type );


	~Texture();


	void generate();
	void load( bool flip = false );
	void bind();

};



#endif

