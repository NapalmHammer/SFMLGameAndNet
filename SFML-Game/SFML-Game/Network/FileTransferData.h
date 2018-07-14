#pragma once
#include <fstream>
#include <memory>
#include <SFML\Network.hpp>
struct FileTransferData
{
	static const int m_BufferSize = 16384;
	std::string m_FileName;
	std::int32_t m_BytesWritten;
	std::int32_t m_FileOffset;
	std::int32_t m_RemainingBytes;
	std::ifstream m_InfileStream;
	std::ofstream m_OutfileStream;
	std::streamoff m_FileSize;
	bool m_TransferInProgress = false;
	char m_Buffer[m_BufferSize];
	bool Initialize(const std::string & fileName, std::string & errMsg);
	std::shared_ptr<sf::Packet> GetOutgoingBufferPacket(std::int32_t& bytes, std::string& msg);
};