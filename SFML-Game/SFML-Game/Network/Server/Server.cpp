#include "Server.h"
#include <iostream>
#include "..\PacketStructs.h"
#include <Windows.h>
#include <SFML\Network.hpp>

Server::Server(int _PORT, bool _LoopBackToLocalHost)
{
	if (m_sListen.listen(_PORT) != sf::Socket::Done)
	{
		std::cout << "Failed m_sListen.listen(_PORT)\n";
		exit(1);
	}
	m_IDCounter = 0;
	std::thread PST(PacketSenderThread, std::ref(*this));
	PST.detach();
	m_threads.emplace_back(&PST);
}

Server::~Server()
{
	m_terminateThreads = true;
	for (std::thread * t : m_threads)
	{
		t->join();
	}
}

bool Server::ListenForNewConnection()
{
	std::shared_ptr<Connection> newConnection;
	if (m_sListen.accept(newConnection->m_socket) != sf::Socket::Done)
	{
		std::cout << "Failed accepting client \n";
		return false;
	}
	else
	{
		std::lock_guard<std::shared_mutex> lock(m_mutex_connectionMgr);
		m_connections.emplace_back(newConnection);
		newConnection->m_ID = m_IDCounter;
		newConnection->m_Name = std::to_string(m_IDCounter);
		m_IDCounter++;
		std::cout << "Client connected! ID:" << newConnection->m_ID << std::endl;
		std::thread CHT(ClientHandlerThread, std::ref(*this), newConnection);
		CHT.detach();
		m_threads.emplace_back(&CHT);
		return true;
	}
}

void Server::ClientHandlerThread(Server & _server, std::shared_ptr<Connection> _connection) //ID = the index in the SOCKET connections array
{
	PacketType packettype;
	while (true)
	{
		if (_server.m_terminateThreads == true)
			break;
		if (!_server.GetPacketType(_connection, packettype)) //Get packet type
			break; //If there is an issue getting the packet type, exit this loop
		if (!_server.ProcessPacket(_connection, packettype)) //Process packet (packet type)
			break; //If there is an issue processing the packet, exit this loop
	}
	std::cout << "Lost connection to client ID: " << _connection->m_ID << std::endl;
	_server.DisconnectClient(_connection); //Disconnect this client and clean up the connection if possible
	return;
}

void Server::PacketSenderThread(Server & server) //Thread for all outgoing packets
{
	while (true)
	{
		if (server.m_terminateThreads == true)
		{
			std::cout << "Failed 1 \n";
			break;
		}
		std::shared_lock<std::shared_mutex> lock(server.m_mutex_connectionMgr);
		for (auto conn : server.m_connections) //for each connection...
		{
			std::cout << "Failed 2\n";
			if (conn->m_pm.HasPendingPackets()) //If there are pending packets for this connection's packet manager
			{
				std::cout << "Failed 3\n";
				auto p = conn->m_pm.Retrieve(); //Retrieve packet from packet manager
				if (!server.SendAll(conn, (const char*)(p->getData()), p->getDataSize())) //send packet to connection
				{
					std::cout << "Failed to send packet to ID: " << conn->m_ID << std::endl; //Print out if failed to send packet
				}
			}
		}
		Sleep(5);
	}
	std::cout << "Ending Packet Sender Thread..." << std::endl;
}

void Server::DisconnectClient(std::shared_ptr<Connection> _connection) //Disconnects a client and cleans up socket if possible
{
	std::lock_guard<std::shared_mutex> lock(m_mutex_connectionMgr); //Lock connection manager mutex since we are possible removing element(s) from the vector
	_connection->m_pm.Clear(); //Clear out all remaining packets in queue for this connection
	_connection->m_socket.disconnect();
	m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), _connection)); //Remove connection from vector of connections
	std::cout << "Cleaned up client: " << _connection->m_ID << "." << std::endl;
	std::cout << "Total connections: " << m_connections.size() << std::endl;
}