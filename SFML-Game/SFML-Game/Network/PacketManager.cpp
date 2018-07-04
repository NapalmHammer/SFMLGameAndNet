#include "PacketManager.h"

void PacketManager::clear()
{
	std::lock_guard<std::mutex> lock(m_Mutex_Packets);
	m_Queue_Packets = std::queue<std::shared_ptr<sf::Packet>>{};
}

bool PacketManager::HasPendingPackets()
{
	std::lock_guard<std::mutex> lock(m_Mutex_Packets);
	return (!m_Queue_Packets.empty());
}

void PacketManager::Append(std::shared_ptr<sf::Packet> p)
{
	std::lock_guard<std::mutex> lock(m_Mutex_Packets);
	m_Queue_Packets.push(std::move(p));
}

std::shared_ptr<sf::Packet> PacketManager::Retrieve()
{
	std::lock_guard<std::mutex> lock(m_Mutex_Packets);
	std::shared_ptr<sf::Packet> p = m_Queue_Packets.front();
	m_Queue_Packets.pop();
	return p;
}
