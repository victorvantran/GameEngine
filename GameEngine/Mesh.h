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


	/**
	 * Create the Vertex Array Object
	 *
	 * Generates the VAO. 
	 * Generates the VBO that the VAO will refer to.
	 * Generate VertexAttribPointers and enables them
	 * Generates the EBO
	 *
	 * @return void
	 */
	void createVAO();



public:
	/**
	 * Gives mesh the necessary data needed to generate a VAO
	 *
	 * Calls createVAO after initializing _vertices, _indices, and _textures
	 *
	 * @return void
	 */
	Mesh( std::vector<Vertex>& vertices, std::vector<std::uint32_t>& indices, std::vector<Texture>& textures );


	~Mesh();


	/**
	 * Render the mesh
	 *
	 * Activates, binds, and sets the proper texture units to the diffuse, specular, normal, and height properties in the shader materials struct.
	 *
	 * @return void
	 */
	void render( Shader& shader );
	


	/**
	 * Render the mesh
	 *
	 * Activates, binds, and sets the proper texture units to the diffuse, specular, normal, and height properties in the shader materials struct.
	 *
	 * @return void
	 */
	void renderInstanced( Shader& shader );


	/**
	 * Deallocates the memory of the GPU
	 *
	 * Deletes VAO, VBO, and EBO
	 *
	 * @return void
	 */
	void cleanup();
};



#endif
