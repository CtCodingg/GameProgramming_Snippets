#include <iostream>

#include "Game.hpp"

int main(int argc, char *argv[])
{
	Game game{ 1920, 1080, 60 };
	game.RunLoop();

	return 0;
}