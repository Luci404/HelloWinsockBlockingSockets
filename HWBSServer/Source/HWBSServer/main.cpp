#include "HWBS/HWBS.h"

#include <iostream>

bool ProcessPacket(HWBS::Packet& packet)
{
	switch (packet.GetPacketType())
	{
	case HWBS::PacketType::PT_ChatMessage:
	{
		std::string message;
		packet >> message;
		std::cout << "Chat Message: " << message << std::endl;
		break;
	}
	case HWBS::PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		packet >> arraySize;
		std::cout << "Array Size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			packet >> element;
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	default:
	{
		break;
	}
	}

	return true;
}

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

					HWBS::Packet packet;
					while (true)
					{

						HWBS::PResult result = newConnection.ReceivePacket(packet);
						if (result != HWBS::PResult::P_Success)
							break;

						if (!ProcessPacket(packet))
							break;
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