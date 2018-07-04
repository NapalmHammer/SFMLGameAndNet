#include "Client.h"

bool Client::ProcessPacket(PacketType _packettype)
{
	switch (_packettype)
	{
	case PacketType::ChatMessage:
	{
		std::string Message;
		if (!GetString(Message))
			return false;
		chatLog->SUpdateLog(Message);
		break;
	}
	case PacketType::FileTransferRequestFile:
	{
		std::string downloadPath = "ClientDownloads\\";
		std::string FileName;
		if (!GetString(FileName))
			return false;
		chatLog->UpdateLog("Client", ("File name Received from server: " + std::string(FileName)));
		std::string errMsg;
		if (m_file.Initialize(FileName, errMsg))
		{
			int bytes;
			std::string msg;
			m_pm.Append(m_file.getOutgoingBufferPacket(bytes, msg));
			chatLog->UpdateLog("Client", "Sent " + std::to_string(bytes) + msg);
		}
		else
		{
			SendString(errMsg);
		}
		break;
	}
	case PacketType::FileTransfer_EndOfFile:
	{
		chatLog->UpdateLog("Client", "File transfer completed, file received.");
		chatLog->UpdateLog("Client", "File size(bytes): " + std::to_string(m_file.m_bytesWritten));
		m_file.m_transferInProgress = false;
		m_file.m_bytesWritten = 0;
		m_file.m_outfileStream.close();
		break;
	}
	case PacketType::FileTransferByteBuffer:
	{
		int32_t buffersize;
		if (!GetInt32_t(buffersize))
		{
			chatLog->UpdateLog("Client", "did not get all of buffersize");
			return false;
		}
		if (buffersize > FileTransferData::m_bufferSize) //If invalid buffer size (too large)
			return false;
		if (!GetAll(m_file.m_buffer, buffersize))
		{
			chatLog->UpdateLog("Client", "did not get all of buffer");
			return false;
		}
		m_file.m_outfileStream.write(m_file.m_buffer, buffersize);
		m_file.m_bytesWritten += buffersize;
		chatLog->UpdateLog("Client", (std::to_string(buffersize) + " Bytes received."));
		std::shared_ptr<sf::Packet> p = std::make_shared<sf::Packet>();
		*p << std::int32_t(PacketType::FileTransferRequestNextBuffer);
		m_pm.Append(p);
		break;
	}
	case PacketType::FileTransferRequestNextBuffer:
	{
		if (m_file.m_transferInProgress)
		{
			std::int32_t bytes;
			std::string msg;
			m_pm.Append(m_file.getOutgoingBufferPacket(bytes, msg));
			chatLog->UpdateLog("Client", "Sent " + std::to_string(bytes) + msg);
		}
		break;
	}
	case PacketType::CancelFileSend:
	{
		if (m_file.m_outfileStream.is_open())
			m_file.m_outfileStream.close();
		m_file.m_transferInProgress = false;
		chatLog->UpdateLog("Server", "Cancelled file send.");
		break;
	}
	default:
		chatLog->UpdateLog("Client", "Unrecognizable packet: " + std::to_string((int32_t)_packettype));
		break;
	}
	return true;
}