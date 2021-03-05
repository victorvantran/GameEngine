#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb/stb_image.h"

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"



class Model
{
public:
    glm::vec3 _position;
    glm::vec3 _scale;


protected:
	std::vector<Mesh> _meshes;
	std::string _directory;
	std::vector<Texture> _textures_loaded;


private:
	GLuint getTextureFromFilez( const char* texturePath, const std::string& directory, bool gamma = false )
	{
		std::string filepath = std::string(directory) + std::string("/") + std::string( texturePath );

		GLuint textureId;
		glGenTextures( 1, &textureId );

		std::int32_t width, height, nrChannels;

		unsigned char* data = nullptr;
		data = stbi_load( filepath.c_str(), &width, &height, &nrChannels, 0 );
		if ( data )
		{
			GLenum format;
			if ( nrChannels == 1 )
			{
				format = GL_RED;
			}
			else if ( nrChannels == 3 )
			{
				format = GL_RGB;
			}
			else if ( nrChannels == 4 )
			{
				format = GL_RGBA;
			}
			else
			{
				std::cout << "Texture has unknown nrChannels at path: " << filepath << std::endl;
				stbi_image_free( data );
				return textureId;
			}

			glBindTexture( GL_TEXTURE_2D, textureId );
			glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data );
			glGenerateMipmap( GL_TEXTURE_2D );

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			stbi_image_free( data );
		}

		return textureId;
	}


public:
	Model( glm::vec3 position, glm::vec3 scale );
	~Model();

	void load( std::string path );

	void processNode( aiNode* node, const aiScene* scene );
	Mesh processMesh( aiMesh* mesh, const aiScene* scene );
	std::vector<Texture> loadMaterialTextures( aiMaterial* material, aiTextureType type );

	void initiate();

	void render( Shader& shader );

	void cleanup();


	/// Getters
	glm::vec3 getPosition() const;

	glm::vec3 getScale() const;

	/// Setters
	void setPosition( glm::vec3 position );

	void setScale( glm::vec3 scale );
};


#endif
