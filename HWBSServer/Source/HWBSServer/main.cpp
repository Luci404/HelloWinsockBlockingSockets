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

			if (socket.Listen(HWBS::IPEndpoint("127.0.0.1", 4790)) == HWBS::PResult::P_Success)
			{
				std::cout << "Socket successfully listening on port 4790." << std::endl;
			
				HWBS::Socket newConnection;
				if (socket.Accept(newConnection) == HWBS::PResult::P_Success)
				{
					std::cout << "New connection accepted." << std::endl;

					char buffer[256];
					int result = HWBS::PResult::P_Success;
					while (result == HWBS::PResult::P_Success)
					{
						result = newConnection.ReceiveAll(buffer, 256);
						if (result != HWBS::PResult::P_Success)
						{
							break;
						}
						std::cout << buffer << std::endl;
					}

					newConnection.Close();
				}
				else
				{
					std::cerr << "Failed to accept new connection." << std::endl;
				}

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

	system("pause");

	return 0;
}