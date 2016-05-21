#include "Game.hpp"
#include <iostream>

int main()
{
	try
	{
		Game game;

		game.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		getchar();

		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
