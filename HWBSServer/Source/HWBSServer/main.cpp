#include "HWBS/HWBS.h"

#include <iostream>

int main()
{
	if (HWBS::Network::Initialize())
	{
		std::cout << "Successfully initialized network" << std::endl;
		
		HWBS::IPEndpoint endpoint("www.google.com", 8080);
		if (endpoint.GetIPVersion() == HWBS::IPVersion::IPv4)
		{
			std::cout << "Hostname: " << endpoint.GetHostname() << std::endl;
			std::cout << "IP: " << endpoint.GetIPString() << std::endl;
			std::cout << "Port: " << endpoint.GetPort() << std::endl;
			std::cout << "IP Bytes: " << std::endl;
			for (uint8_t digit : endpoint.GetIPBytes())
			{
				std::cout << (int)digit << std::endl;
			}
		}
		else
		{
			std::cerr << "This is not an IPv4 address." << std::endl;
		}

		HWBS::Socket socket;
		if (socket.Create() == HWBS::PResult::P_Success)
		{
			std::cout << "Successfully created socket." << std::endl;

			socket.Close();
		}
		else
		{
			std::cout << "Failed to create socket." << std::endl;
		}

	}
	HWBS::Network::Shutdown();
}