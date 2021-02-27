#ifndef GAME_TIME_H
#define GAME_TIME_H

class GameTime
{
private:
	float _deltaTime;
	long double _totalElapsedSeconds;
public:
	GameTime();
	~GameTime();

	/**
	 * Return a float, which is the change of time between each game frame in seconds
	 *
	 * @return float
	 */
	float getDeltaTime() const;


	/**
	 * Return a long double, which is the total amount of time in seconds that the game window has existsed
	 *
	 * @return long double
	 */
	long double getTotalElapsedSeconds() const;


	/**
	 * Updates the delta time to the proper value between frames
	 *
	 * To be called in between frames. Takes the difference between the total elapsed seconds from the previous
	 * frame and the total elapsed seconds from the current frame. Sets the member _totalElaspedSeconds to the
	 * updated value.
	 *
	 * @return float
	 */
	void setDeltaTime( float deltaTime );


	/**
	 * Updates the delta time to the proper value between frames
	 *
	 * To be called in between frames. Calculates a new totalElapsedSeconds to be passed in and set the member 
	 * _totalElaspedSeconds to the updated value.
	 *
	 * @param totalElapsedSeconds a long double representing the totalElapsedSeconds up until the current frame
	 * @return float
	 */
	void setTotalElapsedSeconds( long double totalElapsedSeconds );
};


#endif