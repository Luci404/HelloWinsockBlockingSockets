#include "Socket.h"

#include <assert.h>

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

	SocketHandle Socket::GetHandle()
	{
		return m_Handle;
	}

	IPVersion Socket::GetIPVersion()
	{
		return m_IPVersion;
	}

}