#include "Server.h"
#include "..\PacketStructs.h"

bool Server::GetString(std::shared_ptr<Connection> _connection, std::string &_string)
{
	std::int32_t bufferlength;
	if (!GetInt32_t(_connection, bufferlength))
		return false;
	if (bufferlength == 0) return true;
	_string.resize(bufferlength); //resize string to fit message
	return GetAll(_connection, &_string[0], bufferlength);
}

bool Server::GetPacketType(std::shared_ptr<Connection> _connection, PacketType &_packettype)
{
	int packettype_int;
	if (!GetInt32_t(_connection, packettype_int))
		return false;
	_packettype = (PacketType)packettype_int;
	return true;
}

bool Server::GetInt32_t(std::shared_ptr<Connection> _connection, std::int32_t &_int32_t)
{
	if (!GetAll(_connection, (char*)&_int32_t, sizeof(std::int32_t)))
		return false;
	return true;
}

bool Server::GetAll(std::shared_ptr<Connection> _connection, char* _data, int _totalBytes)
{
	std::size_t bytesReceived = 0;
	while (bytesReceived < _totalBytes)
	{
		auto retnCheck = _connection->m_socket.receive(_data, std::size_t(_totalBytes), bytesReceived);
		if (retnCheck == sf::Socket::Status::Error)
			return false;
		bytesReceived += retnCheck;
	}
	return true;
}

bool Server::SendAll(std::shared_ptr<Connection> _connection, const char* _data, const int _totalBytes)
{
	int bytesSent = 0;
	while (bytesSent < _totalBytes)
	{
		auto retnCheck = _connection->m_socket.send(_data + bytesSent, _totalBytes - bytesSent);
		if (retnCheck == sf::Socket::Status::Error)
			return false;
		bytesSent += retnCheck;
	}
	return true;
}

void Server::SendString(std::shared_ptr<Connection> _connection, const std::string &_string)
{
	PS::ChatMessage message(_string);
	_connection->m_pm.Append(message.toPacket());
}

