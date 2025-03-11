#include <iostream>

#include <Common/Vector2D.hpp>
#include "Game.hpp"

int main(int argc, char *argv[])
{
	Game game{ 1920, 1080, true };
	game.RunLoop();

	return 0;
}