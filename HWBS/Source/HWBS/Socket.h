#pragma once

#include "HWBS/SocketHandle.h"
#include "HWBS/PResult.h"
#include "HWBS/IPVersion.h"
#include "HWBS/IPEndpoint.h"
#include "HWBS/Constants.h"
#include "HWBS/Packet.h"

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
		PResult Listen(IPEndpoint endpoint, int backlog = 5);
		PResult SetSocketOption(SocketOption option, bool enabled);
		PResult Accept(Socket& outSocket);
		PResult Connect(IPEndpoint endpoint);
		PResult Send(const void* data, uint32_t numberOfBytes, int& bytesSent);
		PResult Receive(void* destination, int numberOfBytes, int& bytesReceived);
		PResult SendAll(const void* data, uint32_t numberOfBytes);
		PResult ReceiveAll(void* destination, int numberOfBytes);
		PResult SendPacket(Packet& packet);
		PResult ReceivePacket(Packet& packet);

		SocketHandle GetHandle();
		IPVersion GetIPVersion();

	private:
		SocketHandle m_Handle;
		IPVersion m_IPVersion;
	};


}