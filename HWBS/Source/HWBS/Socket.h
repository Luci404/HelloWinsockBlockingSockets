#pragma once

#include "HWBS/SocketHandle.h"
#include "HWBS/PResult.h"
#include "HWBS/IPVersion.h"
#include "HWBS/IPEndpoint.h"

namespace HWBS
{
	enum class SocketOption
	{
		TCP_NoDelay, // TRUE = Disable Negle's Algorithn
	};

	class Socket
	{
	public: 
		Socket(IPVersion ipVersion = IPVersion::IPv4, SocketHandle handle = INVALID_SOCKET);

		PResult Create();
		PResult Close();
		PResult Bind(IPEndpoint endpoint);
		PResult SetSocketOption(SocketOption option, bool enabled);

		SocketHandle GetHandle();
		IPVersion GetIPVersion();
	

	private:
		SocketHandle m_Handle;
		IPVersion m_IPVersion;
	};


}