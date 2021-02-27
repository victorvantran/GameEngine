#ifndef MESH_H
#define MESH_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb/stb_image.h"
#include "Vertex.h"

class Mesh
{
private:

protected:
	enum class VBO
	{
		Position,
		count
	};

	enum class EBO
	{
		Position,
		count
	};

	GLuint _vao;
	GLuint _vbo[( std::size_t )VBO::count];
	GLuint _ebo[( std::size_t )EBO::count];
	std::uint64_t _vertexCount;
	std::uint64_t _elementCount;

public:
	Mesh();


	virtual ~Mesh();


	/**
	 * Helper function to load in source code from a shader file path
	 *
	 * @param verticies a pointer to an array of Vertex
	 * @param numVerticies a size_t representing the number of Vertex
	 * @param indicies a pointer to an array of index used to draw by element
	 * @param numIndices a size_t representing the number of elements to draw
	 * @return void
	 */
	void loadPrimitives( Vertex* vertices, std::size_t numVertices, std::uint32_t* indices, std::size_t numIndices );


	/**
	 * Binds to the Vertex Array Object (VAO) of the mesh and calls openGL draw method
	 *
	 * @return void
	 */
	virtual void draw();
};


#endif