#include "PacketStructs.h"
#include <SFML\Network.hpp>

namespace PS
{
	ChatMessage::ChatMessage(const std::string _msg)
		:m_Message(_msg)
	{
	}

	std::shared_ptr<sf::Packet> ChatMessage::toPacket()
	{
		std::shared_ptr<sf::Packet> p = std::make_shared<sf::Packet>();
		*p << std::int32_t(PacketType::ChatMessage);
		*p << m_Message.size();
		*p << m_Message;
		return p;
	}

	std::shared_ptr<sf::Packet> FileDataBuffer::toPacket()
	{
		std::shared_ptr<sf::Packet> p = std::make_shared<sf::Packet>();
		*p << std::int32_t(PacketType::FileTransferByteBuffer);
		*p << m_Size;
		*p << m_DataBuffer, m_Size;
		return p;
	}
	FileTransferRequestFile::FileTransferRequestFile(const std::string _fileName)
		:m_FileName(_fileName)
	{
	}
	std::shared_ptr<sf::Packet> FileTransferRequestFile::toPacket()
	{
		std::shared_ptr<sf::Packet> p = std::make_shared<sf::Packet>();
		*p << std::int32_t(PacketType::FileTransferRequestFile);
		*p << std::int32_t(m_FileName.size());
		*p << m_FileName;
		return p;
	}
}
