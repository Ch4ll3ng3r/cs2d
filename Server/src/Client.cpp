#include "../include/Client.hpp"

CClient::CClient (sf::TcpSocket *pTcpSocket, sf::UdpSocket *pUdpSocket)
{
    m_pTcpSocket = pTcpSocket;
    m_pUdpSocket = pUdpSocket;
    m_pTcpSocket->setBlocking (false);
    m_RemoteIp = m_pTcpSocket->getRemoteAddress ();
    m_usLocalPort = m_pTcpSocket->getLocalPort ();
    m_usRemotePort = m_usLocalPort + 1;
    cout << "a new player has connected" << endl;
    cout << "ip: " << m_RemoteIp << endl;
    cout << "port: " << m_usRemotePort << endl;
}

CClient::~CClient ()
{
    m_pTcpSocket = nullptr;
    m_pUdpSocket = nullptr;
}

CPlayer* CClient::GetPlayer ()
{
    return &m_Player;
}

void CClient::Send (sf::Packet packet)
{
    if (m_pUdpSocket->send (packet, m_RemoteIp, m_usRemotePort) != sf::Socket::Done) {}
}

void CClient::Receive ()
{
    sf::Packet packet;
    sf::Vector2<float> fPlayerPos;
    float fPlayerDirection = 0.f;

    // Receive Packet
    if (m_pUdpSocket->receive (packet, m_RemoteIp, m_usRemotePort) != sf::Socket::Done) {}
    else
    {
        // Extract Packet
        if (packet >> fPlayerPos.x >> fPlayerPos.y >> fPlayerDirection)
        {
            m_Player.SetPos (fPlayerPos);
            m_Player.SetDirection (fPlayerDirection);
        }
        else
            cout << "failed to extract packet received from " << m_RemoteIp << endl;
    }

}
