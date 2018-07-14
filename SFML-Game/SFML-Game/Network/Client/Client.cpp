#include "Client.h"
#include "..\PacketStructs.h"


void Client::ClientThread(Client& _client)
{
	PacketType packettype;
	while (true)
	{
		if (_client.m_terminateThreads)
		{
			break;
		}
		if (!_client.GetPacketType(packettype))
		{
			break;
		}
		if (!_client.ProcessPacket(packettype))
		{
			break;
		}
	}
	_client.conState = Disconnected;
	_client.m_terminateThreads = true;
}

void Client::PacketSenderThread(Client& _client)
{
	while (true)
	{
		if (_client.m_terminateThreads == true)
			break;
		if (_client.m_pm.HasPendingPackets())
		{
			auto p = _client.m_pm.Retrieve();

			if (!_client.SendAll((const char*)(p->getData()), p->getDataSize()))
				break;
		}
	}
}

void Client::Update()
{
	if (!m_terminateThreads)
	{
		if (conState == Disconnected)
		{
			Disconnect();
			conState = Idle;
		}
	}
}

bool Client::RequestFile(const std::string& _fileName)
{
	if (m_isConnected)
	{
		if (m_file.m_TransferInProgress)
		{
			//chatLog->UpdateLog("Client", "UHOH: Function(Client::RequestFile) - File Transfer already in progress.\n");
			return false;
		}
		m_file.m_TransferInProgress = true;
		//std::string path = "ClientDownloads\\";
		m_file.m_OutfileStream.open(/*path +*/ _fileName, std::ios::binary);
		//chatLog->UpdateLog("Client", "Opening " + /*path +*/ _fileName + " for writing file to.");

		if (!m_file.m_OutfileStream.is_open())
		{
			//chatLog->UpdateLog("Client", "File " + /*path +*/ _fileName + " Is not open.");
			m_file.m_OutfileStream.open(/*path +*/ _fileName, std::ios::binary);
		}
		m_file.m_FileName = _fileName;
		m_file.m_BytesWritten = 0;
		if (!m_file.m_OutfileStream.is_open())
		{
			//chatLog->UpdateLog("Client", "UHOH: Function(Client::Requestfile) - Unable to open file: " + _fileName + " for writing.\n");
			return false;
		}
		//chatLog->UpdateLog("Client", "Requesting file from server: " + _fileName);
		sf::Packet requestFilePacket;
		requestFilePacket << std::int32_t(PacketType::FileTransferRequestFile);
		requestFilePacket << m_file.m_FileName.size();
		requestFilePacket << m_file.m_FileName.c_str();
		requestFilePacket << m_file.m_FileName.size();
		m_pm.Append(std::make_shared<sf::Packet>(requestFilePacket));
		//chatLog->UpdateLog("Client", "Received file name: " + _fileName + " from server.");
		return true;
	}
	else
	{
		//chatLog->UpdateLog("Client", "ERROR: USER IS A DUMBER THAN DIRT, TRIED TO GET A FILE WHILE NOT CONNECTED TO ANYTHING. REEEEEEEE.");
		return false;
	}
}

bool Client::SendFile(const std::string& _fileName)
{
	if (m_isConnected)
	{
		sf::Packet ClientSendFile;
		ClientSendFile << std::int32_t(PacketType::ClientSendFileRequest);
		ClientSendFile << _fileName.size();
		ClientSendFile << _fileName.c_str();
		ClientSendFile << _fileName.size();
		m_pm.Append(std::make_shared<sf::Packet>(ClientSendFile));
		return true;
	}
	else
	{
		//chatLog->UpdateLog("Client", "Wow, user tried to send a file while not connected to anything. REEEEEEEEEEEE");
		return false;
	}
}

void Client::SetName(const std::string _name)
{
	if (m_isConnected)
	{
		sf::Packet ClientSendFile;
		ClientSendFile << std::int32_t(PacketType::ClientSetName);
		ClientSendFile << _name.size();
		ClientSendFile << _name.c_str();
		ClientSendFile << _name.size();
		m_pm.Append(std::make_shared<sf::Packet>(ClientSendFile));
		userName = _name;
		//chatLog->UpdateLog("Client", "Set name on server to " + _name);
	}
	else
	{
		//chatLog->UpdateLog("Client", "You can't set your name on a server you aren't connected to. Kill yourself.");
	}
}

void Client::HandleInput(const std::string& _message)
{
	switch (_message[0])
	{
	case '/':
	{
		if (_message == "/exit" || _message == "/Exit")
		{
			//chatLog->OutputLog();
			Disconnect();
			exit(0);
		}
		else
		{
			//chatLog->UpdateLog("Client", "That isn't a // command. Take a dump on the floor.");
		}

		break;
	}
	default:
		if (_message.size() < 1)
			break;
		//chatLog->UpdateLog(userName, _message);
		SendString(":" + _message);
		break;
	}
}

// ClientIni.cpp stuff

Client::Client(std::string _yesORno, int _PORT)
{
	m_port = _PORT;
	conState = Idle;
}

bool Client::Connect()
{
	if (m_isConnected)
		return false;
	if (m_connection.connect("127.0.0.1", m_port) == sf::Socket::Status::Error)
	{
		//MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	conState = Connected;
	m_isConnected = true;
	m_terminateThreads = false;
	//chatLog->UpdateLog("Client", "Connecte to server!");

	if (m_pst.joinable())
		m_pst.join();
	if (m_ct.joinable())
		m_ct.join();
	m_pst = std::thread(PacketSenderThread, std::ref(*this)); //Create thread to send packets
	m_ct = std::thread(ClientThread, std::ref(*this)); //Create thread to listen to server
	return true;
}

void Client::Disconnect()
{
	if (m_isConnected)
	{
		CloseConnection();
		m_pm.Clear();
		if (m_pst.joinable())
			m_pst.join();
		if (m_ct.joinable())
			m_ct.join();
		if (m_file.m_InfileStream.is_open())
			m_file.m_InfileStream.close();
		if (m_file.m_OutfileStream.is_open())
			m_file.m_OutfileStream.close();
		m_file.m_TransferInProgress = false;
		m_isConnected = false;

		//chatLog->UpdateLog("Client", "Disconnected from server");
	}
	else
	{
		//chatLog->UpdateLog("Client", "Dummy, You can't disconnect if the socket isn't connected to anything. Get Schwifty.");
	}

}

bool Client::CloseConnection()
{
	m_terminateThreads = true;
	m_connection.disconnect();
	return true;
}

Client::~Client()
{
	CloseConnection();
	if (m_ct.joinable())
		m_ct.join();
	if (m_pst.joinable())
		m_pst.join();
}