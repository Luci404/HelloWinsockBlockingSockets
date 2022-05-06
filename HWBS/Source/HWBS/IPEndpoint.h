#pragma once

#include "HWBS/IPVersion.h"

#include <string>
#include <vector>

namespace HWBS
{
	class IPEndpoint
	{
	public:
		IPEndpoint(std::string ipAddress, uint16_t port);
		
		IPVersion GetIPVersion();
		std::string GetHostname();
		std::string GetIPString();
		std::vector<uint8_t> GetIPBytes();
		uint16_t GetPort();

	private:
		IPVersion m_IPVersion;
		std::string m_Hostname;
		std::string m_IPString;
		std::vector<uint8_t> m_IPBytes;
		uint16_t m_Port;
	};
}