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

		data.resize(stringSize);
		data.assign((char*)&Buffer[ExtractionOffset], stringSize);
		ExtractionOffset += stringSize; 

		return *this;
	}

	Packet& Packet::operator>>(uint32_t& data)
	{
		data = *reinterpret_cast<uint32_t*>(&Buffer[ExtractionOffset]);
		data = ntohl(data);
		ExtractionOffset += sizeof(uint32_t);
		return *this;
	}
}