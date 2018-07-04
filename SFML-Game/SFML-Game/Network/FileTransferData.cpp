#include "FileTransferData.h"
#include "PacketStructs.h"
bool FileTransferData::Initialize(const std::string & fileName, std::string & errMsg)
{
	//std::string downloadPath = "ClientDownloads\\";
	if (m_transferInProgress) //If transfer already in progress?
	{
		errMsg = "File Transfer already in progress. File Transfer Request denied.";
		return false;
	}

	m_infileStream.open( /*downloadPath +*/ fileName, std::ios::binary | std::ios::ate); //Open file to read in binary | ate mode. We use ate so we can use tellg to get file size. We use binary because we need to read bytes as raw data
	if (!m_infileStream.is_open()) //If file is not open? (Error opening file?)
	{
		errMsg = "Requested file: " + fileName + " was not found.";
		return false;
	}

	m_fileName = fileName; //set file name just so we can print it out after done transferring
	m_fileSize = m_infileStream.tellg(); //Get file size
	m_infileStream.seekg(0); //Set cursor position in file back to offset 0 for when we read file
	m_fileOffset = 0; //Update file offset for knowing when we hit end of file
	m_transferInProgress = true;
	return true;
}

std::shared_ptr<sf::Packet> FileTransferData::getOutgoingBufferPacket(std::int32_t& bytes, std::string& msg)
{
	std::int32_t m_remainingBytes = (std::int32_t)m_fileSize - m_fileOffset; //calculate remaining bytes
	if (m_remainingBytes > m_bufferSize) //if remaining bytes > max byte buffer
	{
		PS::FileDataBuffer fileData; //Create FileDataBuffer packet structure
		m_infileStream.read(fileData.m_dataBuffer, m_bufferSize); //read in max buffer size bytes
		fileData.m_size = m_bufferSize; //Set FileDataBuffer buffer size
		m_fileOffset += m_bufferSize; //increment fileoffset by # of bytes written
		bytes = m_bufferSize;
		msg = " Bytes.";
		return fileData.toPacket(); //Append fileData packet to packet manager
	}
	else
	{
		PS::FileDataBuffer fileData; //Create FileDataBuffer packet structure
		m_infileStream.read(fileData.m_dataBuffer, m_remainingBytes); //read in remaining bytes
		fileData.m_size = m_remainingBytes; //Set FileDataBuffer remaining bytes
		m_fileOffset += m_remainingBytes; //increment fileoffset by # of bytes written
		bytes = m_remainingBytes;
		msg = " Bytes. File transfer completed.";
		std::shared_ptr<sf::Packet> outgoingPacket = fileData.toPacket();
		*outgoingPacket << int32_t(PacketType::FileTransfer_EndOfFile);
		m_transferInProgress = false;
		m_infileStream.close();
		return outgoingPacket; //Append fileData packet to packet manager
	}
}