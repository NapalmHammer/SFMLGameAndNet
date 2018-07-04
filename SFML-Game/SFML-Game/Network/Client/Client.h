#pragma once
#include <string>
#include "..\FileTransferData.h"
#include "..\PacketManager.h"
#include "..\PacketType.h"
#include "..\Chat\ChatLog.h"

class Client
{
public:
	enum ConnectionState
	{
		Idle,
		Connected,
		Disconnected
	};
	Client(std::string _yesORno, const int _PORT);
	void Update();
	bool Connect();
	void Disconnect();
	bool CloseConnection();
	void SendString(const std::string& _string);
	bool RequestFile(const std::string& _fileName);
	bool SendFile(const std::string& _fileName);
	void SetName(const std::string _name);
	void HandleInput(const std::string& _message);
	ChatLog& GetChatLog() { return *chatLog; };
	~Client();
private:
	//-- Processing methods
	bool ProcessPacket(const PacketType _packettype);

	//-- Thread methods
	static void ClientThread(Client& _client);
	static void PacketSenderThread(Client& _client);

	//-- Send methods
	bool SendAll(const char* _data, const std::int32_t _totalBytes);

	//-- Get methods
	bool GetAll(char* data, const std::int32_t _totalBytes);
	bool GetInt32_t(std::int32_t& _int32_t);
	bool GetPacketType(PacketType &_packettype);
	bool GetString(std::string &_string);
private:
	FileTransferData m_file;
	PacketManager m_pm; //Packet Manager
	sf::TcpSocket m_connection; // TCP socket
	ConnectionState conState; // Connection State
	std::int32_t m_port;
	bool m_terminateThreads = false;
	bool m_isConnected = false;
	std::thread m_pst; //Packet Sender Thread
	std::thread m_ct; //Create thread to listen to server

	std::string userName;
	ChatLog* chatLog;
};