#include "Model.h"



Model::Model( glm::vec3 position, glm::vec3 scale )
	: _position( position ), _scale( scale )
{}

Model::~Model() {}



void Model::initiate() {}




void Model::load( std::string path )
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );

	if ( scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr )
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	this->_directory = path.substr( 0, path.find_last_of( "/" ) );
	processNode( scene->mRootNode, scene );

	return;
}



void Model::processNode( aiNode* node, const aiScene* scene )
{
	// Process all the node's meshes
	for ( std::size_t i = 0; i < node->mNumMeshes; i++ )
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->_meshes.push_back( processMesh( mesh, scene ) );
	}

	// Then process all the node's children
	for ( std::size_t j = 0; j < node->mNumChildren; j++ )
	{
		processNode( node->mChildren[j], scene );
	}

	return;
}



Mesh Model::processMesh( aiMesh* mesh, const aiScene* scene )
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

		//std::cout << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << std::endl;


		vertex.normal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		//std::cout << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << std::endl;


		if ( mesh->mTextureCoords[0] != nullptr )
		{
			vertex.textureCoordinates = glm::vec2( mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y );
			//std::cout << vertex.textureCoordinates.x << ", " << vertex.textureCoordinates.y  << std::endl;
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

	return Mesh( vertices, indices, textures );
}





std::vector<Texture> Model::loadMaterialTextures( aiMaterial* material, aiTextureType type )
{
	// Helper function to load the textures from assimp material to its respective texture type
	// Iterate through all texture location of a particular texture type, parses and stores the data into a Texture struct

	std::vector<Texture> textures;

	for ( std::size_t i = 0; i < material->GetTextureCount( type ); i++ )
	{
		aiString str;
		material->GetTexture( type, i, &str );
		std::cout << str.C_Str() << std::endl;

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
			texture.load( false );
			textures.push_back( texture );
			this->_textures_loaded.push_back( texture );
		}
	}

	return textures;
}


void Model::render( Shader& shader )
{
	/*
	glm::mat4 model = glm::mat4( 1.0f );
	model = glm::translate( model, this->_position );
	model = glm::scale( model, this->_scale );
	model = glm::rotate( model, glm::radians( 90.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
	shader.setMat4( "model", model );
	shader.setFloat( "material.shininess", 0.5f );
	*/


	glm::mat4 model = glm::mat4( 1.0f );
	model = glm::translate( model, this->_position );
	model = glm::scale( model, this->_scale );
	//model = glm::rotate( model, std::sinf( ( float )glfwGetTime() ) * 5.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	shader.setMat4( "model", model );
	shader.setFloat( "material.shininess", 32.0f );

	
	for ( Mesh& mesh : this->_meshes )
	{
		mesh.render( shader );
	}
	



	return;
}

void Model::cleanup() // [!]
{

}




