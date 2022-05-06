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

			socket.Close();
		}
		else
		{
			std::cout << "Failed to create socket." << std::endl;
		}

	}
	HWBS::Network::Shutdown();
}