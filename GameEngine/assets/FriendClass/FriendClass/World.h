#pragma once

#include "Lighting.h"

class World
{
private:
	int _member;
public:
	friend class Lighting;


	World() : _member( 0 ) {}
	World( int member_ ) : _member( member_ ) {}
	~World() {}
};