#include "Client.h"
#include "PacketStructs.h"
bool Client::GetAll(char* _data, std::int32_t _totalBytes)
{
	size_t bytesReceived = 0;
	int totalBytesReceived = 0;
	while (totalBytesReceived < _totalBytes)
	{
		auto retnCheck = m_connection.receive(_data + totalBytesReceived, _totalBytes - totalBytesReceived, bytesReceived);
		if (retnCheck == sf::Socket::Status::Error)
			return false;
		totalBytesReceived += bytesReceived;
	}
	return true;
}

bool Client::SendAll(const char* _data, const std::int32_t _totalBytes)
{
	std::size_t bytesSent = 0;
	int totalBytesSent = 0;
	while (totalBytesSent < _totalBytes)
	{
		auto retnCheck = m_connection.send(_data + totalBytesSent, _totalBytes - totalBytesSent, bytesSent);
		if (retnCheck == sf::Socket::Status::Error)
			return false;
		totalBytesSent += bytesSent;
	}
	return true;
}

bool Client::GetInt32_t(std::int32_t& _int32_t)
{
	if (!GetAll((char*)&_int32_t, sizeof(std::int32_t)))
		return false;
	return true;
}

bool Client::GetPacketType(PacketType &_packettype)
{
	std::int32_t packetType_int;
	if (!GetInt32_t(packetType_int))
		return false;
	_packettype = (PacketType)packetType_int;
	return true;
}

void Client::SendString(const std::string& _string)
{
	PS::ChatMessage message(_string);
	m_pm.Append(message.toPacket());
}

bool Client::GetString(std::string& _string)
{
	std::int32_t bufferlength;
	if (!GetInt32_t(bufferlength))
		return false;
	if (bufferlength == 0) return true;
	_string.resize(bufferlength); //resize string to fit message
	return GetAll(&_string[0], bufferlength);
}