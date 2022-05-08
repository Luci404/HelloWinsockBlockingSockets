#include "HWBS/Packet.h"


namespace HWBS
{
	void Packet::Clear()
	{
		Buffer.clear();
		ExtractionOffset = 0;
	}

	void Packet::Append(const void* data, uint32_t size)
	{
		if ((Buffer.size() + size) > g_MaxPacketSize)
		{
			throw PacketException("[Packet::Append(const void*, uint32_t)] - Packet size exceeded max packet size.");
		}

		Buffer.insert(Buffer.end(), (char*)data, (char*)data + size);
	}

	Packet& Packet::operator<<(uint32_t data)
	{
		data = htonl(data);
		Append(&data, sizeof(uint32_t));
		return *this;
	}

	Packet& Packet::operator<<(std::string data)
	{
		*this << (uint32_t)data.size();
		Append(data.data(), data.size());
		return *this;
	}

	Packet& Packet::operator>>(std::string& data)
	{
		data.clear();

		uint32_t stringSize = 0;
		*this >> stringSize;

		if ((ExtractionOffset + stringSize) > Buffer.size())
		{
			throw PacketException("[Packet::operator>>(std::string&)] - Extraction offset exceeded buffer size.");
		}

		data.resize(stringSize);
		data.assign((char*)&Buffer[ExtractionOffset], stringSize);
		ExtractionOffset += stringSize; 

		return *this;
	}

	Packet& Packet::operator>>(uint32_t& data)
	{
		if ((ExtractionOffset + sizeof(uint32_t)) > Buffer.size())
		{
			throw PacketException("[Packet::operator>>(uint32_t&)] - Extraction offset exceeded buffer size.");
		}

		data = *reinterpret_cast<uint32_t*>(&Buffer[ExtractionOffset]);
		data = ntohl(data);
		ExtractionOffset += sizeof(uint32_t);
		return *this;
	}
}