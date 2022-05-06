#include "HWBS/HWBS.h"

#include <iostream>

int main()
{
	if (HWBS::Network::Initialize())
	{
		std::cout << "Successfully initialized network" << std::endl;
		
		HWBS::Socket socket;
		if (socket.Create() == HWBS::PResult::P_Success)
		{
			std::cout << "Successfully created socket." << std::endl;

			// 127.0.0.1 is the loopback address, only connection from this mashine can connect.
			/*if (socket.Bind(HWBS::IPEndpoint("127.0.0.1", 4790)) == HWBS::PResult::P_Success)
			{
				std::cout << "Socket successfully bound on port 4790." << std::endl;
			}
			else
			{
				std::cout << "Failed to bind socket to port 4790." << std::endl;
			}*/

			if (socket.Listen(HWBS::IPEndpoint("127.0.0.1", 4790)) == HWBS::PResult::P_Success)
			{
				std::cout << "Socket successfully listening on port 4790." << std::endl;
			}
			else
			{
				std::cout << "Failed to listen on port 4790." << std::endl;
			}

			socket.Close();
		}
		else
		{
			std::cout << "Failed to create socket." << std::endl;
		}

	}
	HWBS::Network::Shutdown();
}