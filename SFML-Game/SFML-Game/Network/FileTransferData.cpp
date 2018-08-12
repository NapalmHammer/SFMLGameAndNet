#include "FileTransferData.h"
#include "PacketStructs.h"
bool FileTransferData::Initialize(const std::string & fileName, std::string & errMsg)
{
	if (m_TransferInProgress)
	{
		errMsg = "File Transfer already in progress. File Transfer Request denied.";
		return false;
	}

	m_InfileStream.open( fileName, std::ios::binary | std::ios::ate); 
	if (!m_InfileStream.is_open())
	{
		errMsg = "Requested file: " + fileName + " was not found.";
		return false;
	}

	m_FileName = fileName; 
	m_FileSize = m_InfileStream.tellg();
	m_InfileStream.seekg(0); 
	m_FileOffset = 0; 
	m_TransferInProgress = true;
	return true;
}

std::shared_ptr<sf::Packet> FileTransferData::GetOutgoingBufferPacket(std::int32_t& bytes, std::string& msg)
{
	std::int32_t m_remainingBytes = (std::int32_t)m_FileSize - m_FileOffset; //calculate remaining bytes
	if (m_remainingBytes > m_BufferSize)
	{
		PS::FileDataBuffer fileData; 
		m_InfileStream.read(fileData.m_DataBuffer, m_BufferSize); //read in max buffer size bytes
		fileData.m_Size = m_BufferSize; 
		m_FileOffset += m_BufferSize;
		bytes = m_BufferSize;
		msg = " Bytes.";
		return fileData.toPacket(); 
	}
	else
	{
		PS::FileDataBuffer fileData;
		m_InfileStream.read(fileData.m_DataBuffer, m_remainingBytes); //read in remaining bytes
		fileData.m_Size = m_remainingBytes;
		m_FileOffset += m_remainingBytes;
		bytes = m_remainingBytes;
		msg = " Bytes. File transfer completed.";
		std::shared_ptr<sf::Packet> outgoingPacket = fileData.toPacket();
		*outgoingPacket << int32_t(PacketType::FileTransfer_EndOfFile);
		m_TransferInProgress = false;
		m_InfileStream.close();
		return outgoingPacket;
	}
}