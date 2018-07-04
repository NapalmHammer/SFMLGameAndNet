#pragma once
#include "PacketType.h"
#include "FileTransferData.h"
#include <string>
#include <memory>
#include <SFML\Network.hpp>

namespace PS
{
	class ChatMessage
	{
	public:
		ChatMessage(const std::string & str);
		std::shared_ptr<sf::Packet> toPacket();
	private:
		std::string m_message;
	};

	class FileDataBuffer
	{
	public:
		std::shared_ptr<sf::Packet> toPacket();
		char m_dataBuffer[FileTransferData::m_bufferSize];
		std::int32_t m_size;
	};
}