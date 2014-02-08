#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

#include "Player.hpp"
#include <iostream>

using namespace std;

class CClient
{
    public:
        CClient (sf::TcpSocket *pTcpSocket, sf::UdpSocket *pUdpSocket);
        ~CClient ();
        CPlayer* GetPlayer ();
        void Send (sf::Packet packet);
        void Receive ();

    private:
        sf::IpAddress m_RemoteIp;
        unsigned short m_usLocalPort;
        unsigned short m_usRemotePort;
        sf::TcpSocket *m_pTcpSocket;
        sf::UdpSocket *m_pUdpSocket;
        CPlayer m_Player;
};

#endif // CLIENT_HPP_INCLUDED
