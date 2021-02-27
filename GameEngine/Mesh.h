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

	bool _loaded;
public:
	Mesh();
	virtual ~Mesh() = 0;


	/**
	 * Binds to the Vertex Array Object (VAO) of the mesh and calls openGL draw method
	 *
	 * @return void
	 */
	virtual void draw() = 0;
};


#endif