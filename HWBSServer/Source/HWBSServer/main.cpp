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

					uint32_t a(0), b(0), c(0);
					HWBS::Packet packet;
					while (true)
					{

						HWBS::PResult result = newConnection.ReceivePacket(packet);
						if (result != HWBS::PResult::P_Success)
							break;

						packet >> a >> b >> c;
						std::cout << a << ", " << b << ", " << c << std::endl;
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