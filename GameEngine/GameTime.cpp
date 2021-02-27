#include "GameTime.h"


GameTime::GameTime() : _deltaTime( 0.0f ), _totalElapsedSeconds( 0.0 ) {}
GameTime::~GameTime() {}


float GameTime::getDeltaTime() const
{
	return this->_deltaTime;
}


long double GameTime::getTotalElapsedSeconds() const
{
	return this->_totalElapsedSeconds;
}


void GameTime::setDeltaTime( float deltaTime )
{
	this->_deltaTime = deltaTime;
	return;
}


void GameTime::setTotalElapsedSeconds( long double totalElapsedSeconds )
{
	this->_totalElapsedSeconds = totalElapsedSeconds;
	return;
}