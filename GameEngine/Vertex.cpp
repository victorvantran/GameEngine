#include "Vertex.h"


Vertex::Vertex() : position(), normal(), textureCoordinates() {}


Vertex::Vertex( const glm::vec3& position_, const glm::vec3& normal_, const glm::vec2& textureCoordinates_ ) : position( position_ ), normal( normal_ ), textureCoordinates( textureCoordinates_ ) {}


Vertex::~Vertex() {}

