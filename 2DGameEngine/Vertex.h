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
	Vertex() : _position(), _color(), _textureCoordinates() {}
	Vertex( const glm::vec3& position, const glm::vec4& color, const glm::vec2& textureCoordinates )  : _position( position ), _color( color ), _textureCoordinates( textureCoordinates ) {}
	~Vertex() {}


	// Getters
	glm::vec3 getPosition() const
	{
		return this->_position;
	}


	glm::vec4 getColor() const
	{
		return this->_color;
	}


	glm::vec2 getTextureCoordinates() const
	{
		return this->_textureCoordinates;
	}
};



#endif
