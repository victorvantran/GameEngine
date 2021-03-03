#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
protected:

public:
	Vertex();


	Vertex( const glm::vec3& position, const glm::vec3& normal, const glm::vec2& textureCoordinates );
	
	
	~Vertex();
};



#endif
