#pragma once

#include "HWBS/PacketException.h"
#include "HWBS/Constants.h"
#include "HWBS/PacketType.h"

#define WIN32_LEAN_AND_MEAN
#include <vector>
#include <winsock.h>
#include <string>

namespace HWBS
{
	class Packet
	{
	public:
		Packet(PacketType packetType = PacketType::PT_Invalid);
		PacketType GetPacketType();
		void AssignPacketType(PacketType packetType);

		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator<<(uint32_t data);
		Packet& operator>>(uint32_t& data);

		Packet& operator<<(std::string data);
		Packet& operator>>(std::string& data);

	public:
		uint32_t ExtractionOffset = 0;
		std::vector<uint8_t> Buffer;
	};
}