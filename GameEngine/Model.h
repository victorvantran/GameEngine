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
