#pragma once
#include <vector>
#include <thread>
#include <memory>
#include <shared_mutex>
#include "..\PacketManager.h"
#include "..\PacketType.h"
#include "..\FileTransferData.h"
#include <SFML\Network.hpp>

struct Connection
{
	sf::TcpSocket m_socket;
	PacketManager m_pm;
	FileTransferData m_file;
	std::string m_Name;
	int m_ID = 0;
};

class Server
{
public:
	Server(int _PORT, bool _LoopBackToLocalHost = false);
	~Server();
	bool ListenForNewConnection();
private:
	bool GetString(std::shared_ptr<Connection> _connection, std::string &_string);
	bool GetPacketType(std::shared_ptr<Connection> _connection, PacketType &_packettype);
	bool GetInt32_t(std::shared_ptr<Connection> _connection, int32_t &_int32_t);
	bool GetAll(std::shared_ptr<Connection> _connection, char* data, int totalBytes);
	bool SendAll(std::shared_ptr<Connection> _connection, const char* _data, const int _totalBytes);
	void SendString(std::shared_ptr<Connection> _connection, const std::string& _string);
	bool ProcessPacket(std::shared_ptr<Connection> _connection, PacketType _packettype);
	//-----
	static void ClientHandlerThread(Server& _server, std::shared_ptr<Connection> _connection);
	static void PacketSenderThread(Server& server);
	void DisconnectClient(std::shared_ptr<Connection> _connection);
private:
	std::vector<std::shared_ptr<Connection>> m_connections;
	std::shared_mutex m_mutex_connectionMgr;
	int m_IDCounter = 0;
	sf::TcpListener m_sListen;
	bool m_terminateThreads = false;
	std::vector<std::thread*> m_threads;
};