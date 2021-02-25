#ifndef GAME_TIME_H
#define GAME_TIME_H

class GameTime
{
private:
	float _deltaTime;
	long double _totalElapsedSeconds;
public:
	GameTime() : _deltaTime( 0.0f ), _totalElapsedSeconds( 0.0 ) {}
	~GameTime() {}


	float getDeltaTime() const
	{
		return this->_deltaTime;
	}


	long double getTotalElapsedSeconds() const
	{
		return this->_totalElapsedSeconds;
	}


	void setDeltaTime( float deltaTime )
	{
		this->_deltaTime = deltaTime;
		return;
	}


	void setTotalElapsedSeconds( long double totalElapsedSeconds )
	{
		this->_totalElapsedSeconds = totalElapsedSeconds;
		return;
	}
};


#endif