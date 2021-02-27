#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameTime.h"
#include "RenderManager.h"

class Game
{
protected:
	GameTime _gameTime;
	RenderManager _renderManager;

	std::uint16_t _windowWidth;
	std::uint16_t _windowHeight;
	std::string _windowTitle;





public:
	Game();


	Game( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle );


	~Game();

	/**
	 * The first function to be called after successful construction. Run the game.
	 *
	 * @return void
	 */
	void run();


	/**
	 * Handles input every frame.
	 *
	 * @return void
	 */
	void processInput( GLFWwindow* window );


	/**
	 * To be called immediately when running. Initialize game logics.
	 *
	 * @return void
	 */
	virtual void initialize() = 0;


	/**
	 * To be called after initialization and before the game loop. Load content.
	 *
	 * @return void
	 */
	virtual void loadContent() = 0;


	/**
	 * To be called every frame. Update the game logic.
	 *
	 * @return void
	 */
	virtual void update() = 0;

	/**
	 * To be called every frame. Use the proper shaders and draw the proper meshes.
	 *
	 * @return void
	 */
	virtual void render() = 0;
};


#endif