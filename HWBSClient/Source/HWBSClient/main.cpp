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

				HWBS::Packet stringPacket(HWBS::PacketType::PT_ChatMessage);
				stringPacket << std::string("This is my string packet!");

				HWBS::Packet integerArrayPacket(HWBS::PacketType::PT_IntegerArray);
				const uint32_t arraySize = 6;
				const uint32_t integerArray[arraySize] = { 1, 2, 3, 4, 5, 6 };
				integerArrayPacket << arraySize;
				for (uint32_t i : integerArray) integerArrayPacket << i;


				while (true)
				{
					HWBS::PResult result;

					if (rand() % 2 == 0)
					{
						result = socket.SendPacket(stringPacket);
					}
					else
					{
						result = socket.SendPacket(integerArrayPacket);
					}
					
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