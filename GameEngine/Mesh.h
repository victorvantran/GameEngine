#ifndef MESH_H
#define MESH_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"


class Mesh
{
private:
	std::vector<Vertex>			_vertices;
	std::vector<std::uint32_t>	_indices;
	std::vector<Texture>		_textures;

private:
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;

	void load();
public:
	// Give mesh all necessary data
	Mesh( std::vector<Vertex>& vertices, std::vector<std::uint32_t>& indices, std::vector<Texture>& textures );
	~Mesh();



	// Initialize buffers
	void render( Shader& shader );
	//void draw( Shader& shader );


	void cleanup();
};




#endif
