#ifndef  WOODEN_CHAIR_H
#define WOODEN_CHAIR_H

#include "Model.h"

class WoodenChair : public Model
{
public:
	WoodenChair( glm::vec3 position, glm::vec3 scale )
		: Model( position, scale )
	{
	}

	~WoodenChair()
	{

	}

	void initiate()
	{
		this->load( "assets/models/wooden_chair/scene.obj" );
	}

};


#endif // ! WOODEN_CHAIR_H
