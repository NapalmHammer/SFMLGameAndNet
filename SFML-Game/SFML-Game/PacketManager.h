#pragma once
#include <queue>
#include <mutex>
#include <memory>
#include <SFML/Network.hpp>

class PacketManager
{
private:
	std::queue<std::shared_ptr<sf::Packet>> m_Queue_Packets;
	std::mutex m_Mutex_Packets;
public:
	void clear();
	bool HasPendingPackets();
	void Append(std::shared_ptr<sf::Packet> p);
	std::shared_ptr<sf::Packet> Retrieve();
};