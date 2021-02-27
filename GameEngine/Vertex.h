#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

class Vertex
{
private:
	glm::vec3 _position;
	glm::vec4 _color;
	glm::vec2 _textureCoordinates;
protected:

public:
	Vertex();


	Vertex( const glm::vec3& position, const glm::vec4& color, const glm::vec2& textureCoordinates );
	
	
	~Vertex();


	/**
	 * Returns a glm::vec4 which represents the 3D position of the vector in worldSpace and it's homogeneous coordinate
	 *
	 * @return glm::vec2
	 */
	glm::vec3 getPosition() const;


	/**
	 * Returns a glm::vec4 which represents the rgba values of a vertex
	 *
	 * @return glm::vec2
	 */
	glm::vec4 getColor() const;


	/**
	 * Returns a glm::vec2 which represents the coordinates of the texture that the vertex position maps onto
	 *
	 * @return glm::vec2
	 */
	glm::vec2 getTextureCoordinates() const;
};



#endif
