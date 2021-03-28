#ifndef MODEL_ARRAY_H
#define MODEL_ARRAY_H


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
#include "MeshArray.h"
#include "Texture.h"



class ModelArray
{
public:
	glm::vec3 _position;
	glm::vec3 _scale;


protected:
	std::vector<MeshArray> _meshes;
	std::string _directory;
	std::vector<Texture> _textures_loaded;
	std::vector<glm::vec3> _instances; // for now instances is defined by world position

public:
	ModelArray( glm::vec3 position, glm::vec3 scale )
		: _position( position ), _scale( scale )
	{

	}


	virtual ~ModelArray()
	{

	}


	void load( std::string path )
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );

		if ( scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr )
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		this->_directory = path.substr( 0, path.find_last_of( "/" ) );
		processNodeArray( scene->mRootNode, scene );

		return;
	}


	void loadArray( std::string path )
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );

		if ( scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr )
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		this->_directory = path.substr( 0, path.find_last_of( "/" ) );
		processNodeArray( scene->mRootNode, scene );

		return;
	}


	void processNodeArray( aiNode* node, const aiScene* scene )
	{
		// Process all the node's meshes
		for ( std::size_t i = 0; i < node->mNumMeshes; i++ )
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->_meshes.push_back( processMeshArray( mesh, scene ) );
		}

		// Then process all the node's children
		for ( std::size_t j = 0; j < node->mNumChildren; j++ )
		{
			processNodeArray( node->mChildren[j], scene );
		}

		return;
	}


	MeshArray processMeshArray( aiMesh* mesh, const aiScene* scene )
	{
		// Process Assimp'sdata to our Mesh class data
		std::vector<Vertex> vertices;
		std::vector<std::uint32_t> indices;
		std::vector<Texture> textures;


		// Process vertices by their attributes from assimp mesh object
		for ( std::size_t i = 0; i < mesh->mNumVertices; i++ )
		{
			Vertex vertex;

			vertex.position = glm::vec3(
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z
			);

			vertex.normal = glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			);

			if ( mesh->mTextureCoords[0] != nullptr )
			{
				vertex.textureCoordinates = glm::vec2( mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y );
			}
			else
			{
				vertex.textureCoordinates = glm::vec2( 0.0f, 0.0f );
			}

			vertices.push_back( vertex );
		}


		// Process indices
		// Array of faces, where each is a single primitive (we converted all to triangles by aiProcess_Triangulate ). Face contains indices for its own primitives
		// Iterate through all faces, iterate through all their indices, and store in indices vector
		for ( std::size_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++ )
		{
			aiFace face = mesh->mFaces[faceIndex];
			for ( std::size_t index = 0; index < face.mNumIndices; index++ )
			{
				indices.push_back( face.mIndices[index] );
			}
		}


		// Process Material
		if ( mesh->mMaterialIndex >= 0 )
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffuseMaps = loadMaterialTextures( material, aiTextureType_DIFFUSE );
			textures.insert( textures.end(), diffuseMaps.begin(), diffuseMaps.end() );

			std::vector<Texture> specularMaps = loadMaterialTextures( material, aiTextureType_SPECULAR );
			textures.insert( textures.end(), specularMaps.begin(), specularMaps.end() );
		}

		return MeshArray( vertices, indices, textures, this->_instances );
	}




	std::vector<Texture> loadMaterialTextures( aiMaterial* material, aiTextureType type )
	{
		// Helper function to load the textures from assimp material to its respective texture type
		// Iterate through all texture location of a particular texture type, parses and stores the data into a Texture struct

		std::vector<Texture> textures;

		for ( std::size_t i = 0; i < material->GetTextureCount( type ); i++ )
		{
			aiString str;
			material->GetTexture( type, i, &str );

			bool alreadyLoaded = false;
			for ( std::size_t j = 0; j < this->_textures_loaded.size(); j++ )
			{
				if ( std::strcmp( this->_textures_loaded[j].path.data(), str.C_Str() ) == 0 )
				{
					textures.push_back( this->_textures_loaded[j] );
					alreadyLoaded = true;
					break;
				}
			}

			if ( alreadyLoaded == false )
			{
				Texture texture( this->_directory, str.C_Str(), type );
				texture.load();
				textures.push_back( texture );
				this->_textures_loaded.push_back( texture );
			}
		}

		return textures;
	}


	virtual void initiate()
	{
		// Test initiation [!]
		/*
		float offset = 1.0f;
		for ( int y = -300; y < 300; y += 2 )
		{
			for ( int x = -300; x < 300; x += 2 )
			{
				glm::vec3 translation;
				translation.x = ( float )x / 1.0f + offset;
				translation.y = ( float )y / 1.0f + offset;
				translation.z = 0;
				this->_instances.push_back( translation );
			}
		}
		*/
		srand( glfwGetTime() ); // initialize random seed	

		unsigned int amount = 100000;
		float radius = 50.0;
		float offset = 2.5f;
		for ( unsigned int i = 0; i < amount; i++ )
		{
			glm::mat4 model = glm::mat4( 1.0f );
			// 1. translation: displace along circle with 'radius' in range [-offset, offset]
			float angle = ( float )i / ( float )amount * 360.0f;
			float displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float x = sin( angle ) * radius + displacement;
			displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
			displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float z = cos( angle ) * radius + displacement;
			model = glm::translate( model, glm::vec3( x, y, z ) );

			// 2. scale: scale between 0.05 and 0.25f
			float scale = ( rand() % 20 ) / 100.0f + 0.05;
			model = glm::scale( model, glm::vec3( scale ) );

			// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
			float rotAngle = ( rand() % 360 );
			model = glm::rotate( model, rotAngle, glm::vec3( 0.4f, 0.6f, 0.8f ) );

			// 4. now add to list of matrices
			//modelMatrices[i] = model;


			glm::vec3 translation = glm::vec3(x, y, z);
			this->_instances.push_back( translation );

		}

	}


	void render( Shader& shader )
	{
		for ( MeshArray& meshArray : this->_meshes )
		{
			meshArray.render( shader );
		}
	}


	std::vector<glm::vec3>& getInstances()
	{
		return this->_instances;
	}



	/// Getters
	glm::vec3 getPosition() const
	{
		return this->_position;
	}

	glm::vec3 getScale() const
	{
		return this->_scale;
	}



	/// Setters
	void setPosition( glm::vec3 position )
	{
		this->_position = position;
		return;
	}


	void setScale( glm::vec3 scale )
	{
		this->_scale = scale;
		return;
	}





};

#endif // !MODEL_ARRAY_H
