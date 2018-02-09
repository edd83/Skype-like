#include <sstream>
#include <iostream>
#include "BabelServer.h"
#include "Debug.h"
#include "constant.h"

int	main(int ac, char *argv[])
{
	int port = DEFAULT_SERVER_PORT;
	try
	{
		if (ac > 1)
		{
			std::stringstream ss(argv[1]);
			ss >> port;
		}
		BabelServer babel(port);
		babel.start();
		Debug::Log("> Server properly exited.");
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		Debug::Log("> Server exited.");
	}
	std::cout << std::endl << "Press return to continue." << std::endl;
	std::cin.get();
}
