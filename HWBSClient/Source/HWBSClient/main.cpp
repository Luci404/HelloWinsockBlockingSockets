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

			if (socket.Connect(HWBS::IPEndpoint("127.0.0.1", 4790)) == HWBS::PResult::P_Success)
			{
				std::cout << "Successfully connected to server." << std::endl;

				uint32_t a, b, c;
				a = 4;
				b = 6;
				c = 9;
				HWBS::Packet packet;
				packet << a << b << c;
				while (true)
				{
					HWBS::PResult result = socket.SendPacket(packet);
					if (result != HWBS::PResult::P_Success)
						break;

					std::cout << "Attempting to send chunk of data..." << std::endl;
					Sleep(500);
				}
			}
			else
			{
				std::cerr << "Failed to connect to server." << std::endl;

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