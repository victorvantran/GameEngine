#include "Vertex.h"


Vertex::Vertex() : _position(), _color(), _textureCoordinates() {}


Vertex::Vertex( const glm::vec3& position, const glm::vec4& color, const glm::vec2& textureCoordinates ) : _position( position ), _color( color ), _textureCoordinates( textureCoordinates ) {}


Vertex::~Vertex() {}


glm::vec3 Vertex::getPosition() const
{
	return this->_position;
}


glm::vec4 Vertex::getColor() const
{
	return this->_color;
}


glm::vec2 Vertex::getTextureCoordinates() const
{
	return this->_textureCoordinates;
}