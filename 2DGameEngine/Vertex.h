#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

class Vertex
{
private:
	glm::vec3 _pos;
	glm::vec4 _color;
protected:

public:
	Vertex() : _pos(), _color() {}
	Vertex( const glm::vec3& pos, const glm::vec4& color )  : _pos( pos ), _color( color ) {}
	~Vertex() {}
};



#endif
