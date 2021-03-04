#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <iostream>

#include "Game.h"
#include "TinkerGame.h"


int main()
{
	Game* game = new TinkerGame();
	game->run();

	delete game;
	return 0;
}
