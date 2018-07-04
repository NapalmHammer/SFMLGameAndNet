#include "PacketStructs.h"

namespace PS
{
	ChatMessage::ChatMessage(const std::string & _msg)
		:m_message(_msg)
	{
	}


	std::shared_ptr<sf::Packet> ChatMessage::toPacket()
	{
		std::shared_ptr<sf::Packet> p = std::make_shared<sf::Packet>();
		*p << std::int32_t(PacketType::ChatMessage);
		*p << (m_message.size());
		*p << (m_message);
		return p;
	}

	std::shared_ptr<sf::Packet> FileDataBuffer::toPacket()
	{
		std::shared_ptr<sf::Packet> p = std::make_shared<sf::Packet>();
		*p << std::int32_t(PacketType::FileTransferByteBuffer);
		*p << (m_size);
		*p << (m_dataBuffer, m_size);
		return p;
	}
}