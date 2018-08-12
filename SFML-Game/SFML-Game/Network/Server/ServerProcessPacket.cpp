#include "Server.h"
#include <iostream>
#include "..\PacketStructs.h"

bool Server::ProcessPacket(std::shared_ptr<Connection> _connection, PacketType _packettype)
{
	switch (_packettype)
	{
	case PacketType::ChatMessage:
	{
		std::string message;
		if (!GetString(_connection, message))
			return false;

		PS::ChatMessage cm(_connection->m_Name + message);
		auto chatPacket = cm.toPacket();
		{
			std::shared_lock<std::shared_mutex> lock(m_mutex_connectionMgr);
			for (auto conn : m_connections)
			{
				if (conn == _connection)
					continue;
				conn->m_pm.Append(chatPacket);
			}
		}
		std::cout << "Processed chat message from ID: " << _connection->m_ID << " Sent message: " << message << std::endl;
		break;
	}
	case PacketType::FileTransferByteBuffer:
	{
		int32_t buffersize;
		if (!GetInt32_t(_connection, buffersize))
		{
			std::cout << "Uh oh: GETINT32, BUFFER" << std::endl;
			return false;
		}
		if (!GetAll(_connection, _connection->m_file.m_Buffer, buffersize))
		{
			std::cout << "Uh oh: GETALL, BUFFER-BUFFERSIZE" << std::endl;
			return false;
		}
		_connection->m_file.m_OutfileStream.write(_connection->m_file.m_Buffer, buffersize);
		_connection->m_file.m_BytesWritten += buffersize;
		std::cout << buffersize << " Bytes received." << std::endl;
		auto p = std::make_shared<sf::Packet>();
		*p << std::int32_t(PacketType::FileTransferRequestNextBuffer);
		_connection->m_pm.Append(p);
		break;
	}
	case PacketType::FileTransferRequestFile:
	{
		std::string fileName;
		if (!GetString(_connection, fileName))
			return false;
		std::string errMsg;
		std::cout << "File name Received: " << fileName << std::endl;
		std::cout << "ID: " << _connection->m_ID << " Requesting to get file " << fileName << " on server." << std::endl;
		if (_connection->m_file.Initialize(fileName, errMsg)) //if filetransferdata successfully initialized
		{
			std::int32_t x; // temp vars for debugging
			std::string y;  //
			_connection->m_pm.Append(_connection->m_file.GetOutgoingBufferPacket(x, y)); //Send first buffer from file
		}
		else //If initialization failed, send error message
		{
			SendString(_connection, errMsg);
			std::cout << errMsg << std::endl;
			std::cout << "Cancelling file send" << std::endl;
			auto p = std::make_shared<sf::Packet>(); 
			*p << std::int32_t(PacketType::CancelFileSend);
			_connection->m_pm.Append(p);
		}
		break;
	}
	case PacketType::FileTransferRequestNextBuffer:
	{
		if (_connection->m_file.m_TransferInProgress)
		{
			std::int32_t x; // temp vars for debugging
			std::string y;  //
			_connection->m_pm.Append(_connection->m_file.GetOutgoingBufferPacket(x, y)); //get and send next buffer for file
		}
		break;
	}
	case PacketType::FileTransfer_EndOfFile:
	{
		std::cout << "File transfer completed, file received." << std::endl;
		std::cout << "File Name: " << _connection->m_file.m_FileName << std::endl;
		std::cout << "File size(bytes): " << _connection->m_file.m_BytesWritten << std::endl;
		_connection->m_file.m_BytesWritten = 0;
		_connection->m_file.m_OutfileStream.close();
		break;
	}
	case PacketType::ClientSetName:
	{
		GetString(_connection, _connection->m_Name);
		std::cout << "client " + std::to_string(_connection->m_ID) + " set their name to: " + _connection->m_Name << std::endl;
		break;
	}
	default:
		std::cout << "Unrecognizable packet: " << (int32_t)_packettype << std::endl;
		break;
	}
	return true;
}