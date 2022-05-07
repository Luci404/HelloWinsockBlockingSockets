#include "Socket.h"

#include <assert.h>
#include <iostream>

namespace HWBS
{

	Socket::Socket(IPVersion ipVersion, SocketHandle handle)
		: m_IPVersion(ipVersion), m_Handle(handle)
	{
		assert(m_IPVersion == IPVersion::IPv4);
	}

	PResult Socket::Create()
	{
		assert(m_IPVersion == IPVersion::IPv4);

		if (m_Handle != INVALID_SOCKET)
		{
			return PResult::P_NotYetImplemented;
		}

		m_Handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_Handle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		if (SetSocketOption(SocketOption::TCP_NoDelay, true) != PResult::P_Success)
		{
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::Close()
	{
		if (m_Handle == INVALID_SOCKET)
		{
			return PResult::P_NotYetImplemented;
		}

		int result = closesocket(m_Handle);

		if (result != 0)
		{
			// An error occurred
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		m_Handle = INVALID_SOCKET;

		return PResult::P_Success;
	}

	PResult Socket::Bind(IPEndpoint endpoint)
	{
		sockaddr_in address = endpoint.GetSockaddrIPv4();
		
		int result = bind(m_Handle, (sockaddr*)&address, sizeof(sockaddr_in));
		if (result != 0)
		{
			// An error occurred
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::Listen(IPEndpoint endpoint, int backlog)
	{
		if (Bind(endpoint) != PResult::P_Success)
		{
			return PResult::P_NotYetImplemented;
		}

		int result = listen(m_Handle, backlog);
		if (result != 0)
		{
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::SetSocketOption(SocketOption option, bool enabled)
	{
		BOOL value = enabled ? TRUE : FALSE;

		int result = 0;
		switch (option)
		{
		case SocketOption::TCP_NoDelay:
		{
			result = setsockopt(m_Handle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(BOOL));
			break;
		}
		default:
		{
			return PResult::P_NotYetImplemented;
		}
		}

		if (result != 0)
		{
			// An error occurred
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::Accept(Socket& outSocket)
	{
		sockaddr_in addr = {};
		int len = sizeof(sockaddr_in);
		SocketHandle acceptedConnectionHandle = accept(m_Handle, (sockaddr*)(&addr), &len); // Blocking!
		if (acceptedConnectionHandle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		IPEndpoint newConnectionEndpoint((sockaddr*)&addr);
		std::cout << "Net socket accepted!" << std::endl;
		newConnectionEndpoint.Print();

		outSocket = Socket(IPVersion::IPv4, acceptedConnectionHandle);

		return PResult::P_Success;
	}

	PResult Socket::Connect(IPEndpoint endpoint)
	{
		sockaddr_in addr = endpoint.GetSockaddrIPv4();
		int result = connect(m_Handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
		if (result != 0)
		{
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::Send(void* data, uint32_t numberOfBytes, int& bytesSent)
	{
		bytesSent = send(m_Handle, (const char*)data, numberOfBytes, NULL);

		if (bytesSent == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::Receive(void* destination, int numberOfBytes, int& bytesReceived)
	{
		bytesReceived = recv(m_Handle, (char*)destination, numberOfBytes, NULL);
		
		if (bytesReceived == 0) // If connection was gracefully closed
		{
			return PResult::P_NotYetImplemented;
		}

		if (bytesReceived == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::SendAll(void* data, uint32_t numberOfBytes)
	{
		int totalBytesSent = 0;

		while (totalBytesSent < numberOfBytes)
		{
			int bytesRemaining = numberOfBytes - totalBytesSent;
			int bytesSent = 0;
			char* bufferOffset = (char*)data + totalBytesSent;
			PResult result = Send(bufferOffset, bytesRemaining, bytesSent);
			if (result != PResult::P_Success)
			{
				return PResult::P_NotYetImplemented;
			}
			totalBytesSent += bytesSent;
		}

		return PResult::P_Success;
	}

	PResult Socket::ReceiveAll(void* destination, int numberOfBytes)
	{
		int totalBytesReceived = 0;

		while (totalBytesReceived < numberOfBytes)
		{
			int bytesRemaining = numberOfBytes - totalBytesReceived;
			int bytesReceived = 0;
			char* bufferOffset = (char*)destination + totalBytesReceived;
			PResult result = Receive(bufferOffset, bytesRemaining, bytesReceived);
			if (result != PResult::P_Success)
			{
				return PResult::P_NotYetImplemented;
			}
			totalBytesReceived += bytesReceived;
		}

		return PResult::P_Success;
	}

	SocketHandle Socket::GetHandle()
	{
		return m_Handle;
	}

	IPVersion Socket::GetIPVersion()
	{
		return m_IPVersion;
	}

}