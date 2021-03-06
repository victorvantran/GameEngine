#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Settings.h"
#include "GameTime.h"
#include "Screen.h"
#include "Camera.h"





class Game
{
protected:
	GameTime _gameTime;
	Screen _screen;
	Camera _camera;



private:
	/**
	 * Initalize GLAD to abstract function pointer management of GLFW
	 *
	 * @return bool to indicate a successful GLAD library initialization
	 */
	bool initializeGlad();


	/**
	 * Initiate the screen
	 *
	 * Creates the openGL context, the window, and sets said window as the target of said context
	 *
	 * @return bool to indicate a successful OpenGL context initialization
	 */
	bool initializeScreen();


	/**
	 * Set frame buffer default configurations
	 *
	 * @return void
	 */
	void initializeBufferConfigurations();



public:
	//Game( std::uint16_t width = settings::screen::DEFAULT_WIDTH, std::uint16_t height = settings::screen::DEFAULT_HEIGHT, std::string title = "untitled", bool resizable = false, bool vSynch = true );

	Game();
	~Game();


	/**
	 * The first function to be called after successful construction. Run the game.
	 *
	 * @return void
	 */
	void run();


	/**
	 * To be called immediately when running. Sets up the screen, input, and outputs
	 *
	 * @return void
	 */
	virtual void initialize();

	
	/**
	 * Handles input every frame.
	 *
	 * @return void
	 */
	void processInputs();


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