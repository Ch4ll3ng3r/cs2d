#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include "Client.hpp"
#include <vector>
#include "SafeDelete.hpp"
#include <SFML/Window.hpp>

class CServer
{
    public:
        CServer ();
        ~CServer ();
        void Run ();

    private:
        void SendPackets ();
        void ReceivePackets ();
        void ListenOnIncomingConnections ();
        bool m_bRun;
        sf::Clock m_Clock;
        vector<sf::TcpSocket*> m_vpTcpSockets;
        vector<CClient*> m_vpClients;
        sf::TcpListener m_ListeningSocket;
        sf::UdpSocket m_UdpSocket;
        unsigned int m_uiTickRate;
};

#endif // SERVER_HPP_INCLUDED
