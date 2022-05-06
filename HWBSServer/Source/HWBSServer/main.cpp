#include "HWBS/Network.h"

#include <iostream>

int main()
{
	if (HWBS::Network::Initialize())
	{
		std::cout << "Successfully initialized network" << std::endl;
	}
	HWBS::Network::Shutdown();
}