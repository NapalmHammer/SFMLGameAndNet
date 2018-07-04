#pragma once
#include <fstream>
#include <memory>
#include <SFML\Network.hpp>

struct FileTransferData
{
	static const int m_bufferSize = 16384;
	std::string m_fileName;
	std::int32_t m_bytesWritten;
	std::int32_t m_fileOffset;
	std::streamoff m_fileSize;
	std::int32_t m_remainingBytes;
	std::ifstream m_infileStream;
	std::ofstream m_outfileStream;
	bool m_transferInProgress = false;
	char m_buffer[m_bufferSize];
	bool Initialize(const std::string & fileName, std::string & errMsg);
	std::shared_ptr<sf::Packet> getOutgoingBufferPacket(std::int32_t& bytes, std::string& msg);
};