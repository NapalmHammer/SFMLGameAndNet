#pragma once
#include "FileTransferData.h"
#include "PacketType.h"
#include <memory>
#include <string>
#include <SFML\Network.hpp>

namespace PS
{
	class ChatMessage
	{
	public:
		ChatMessage(const std::string _msg);
		std::shared_ptr<sf::Packet> toPacket();
	private:
		std::string m_Message;
	};

	class FileTransferRequestFile
	{
	public:
		FileTransferRequestFile(const std::string _fileName);
		std::shared_ptr<sf::Packet> toPacket();
	private:
		std::string m_FileName;
	};

	class FileDataBuffer
	{
	public:
		std::shared_ptr<sf::Packet> toPacket();
		char m_DataBuffer[FileTransferData::m_BufferSize];
		int m_Size;
	};
}