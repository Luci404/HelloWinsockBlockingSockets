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

				std::string buffer = "Hello world from client!";
				
				while (true)
				{
					std::cout << "Attempting to send chunk of data..." << std::endl;
					
					uint32_t bufferSize = buffer.size();
					bufferSize = htonl(bufferSize);
					int result = socket.SendAll(&bufferSize, sizeof(uint32_t));
					if (result != HWBS::PResult::P_Success)
						break;

					result = socket.SendAll(buffer.data(), buffer.size());
					if (result != HWBS::PResult::P_Success)
						break;
					
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