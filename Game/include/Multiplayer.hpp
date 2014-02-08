#ifndef MULTIPLAYER_HPP_INCLUDED
#define MULTIPLAYER_HPP_INCLUDED

#include "GameState.hpp"
#include "Collision.hpp"
#include "Movement.hpp"
#include "Shot.hpp"
#include "PacketType.hpp"

class CMultiplayer : public CGameState
{
    public:
        CMultiplayer (map<string, sf::Texture> *pTextures, sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType);
        ~CMultiplayer ();
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents (unsigned int uiElapsed);
        void ProcessMouseEvents (unsigned int uiElapsed);
        void ProcessGameEvents ();
        void CheckCollisions (unsigned int uiElapsed);
        void UpdateView ();
        void Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts);
        void SendPackets (unsigned int uiNow);
        void ReceivePackets (unsigned int uiNow);
        bool ConnectionEstablished ();

    private:
        CMap *m_pMap;
        CPlayer *m_pPlayerLocal;
        CPlayer *m_pPlayerConnected;
        vector<CEvent*> m_vpPendingEvents;
        sf::TcpSocket m_TcpSocket;
        sf::UdpSocket m_UdpSocket;
        sf::IpAddress m_Ip;
        unsigned short m_usLocalPort;
        unsigned short m_usRemotePort;
        bool m_bConnected;
        EPacketType m_CurPacketType;
};

#endif // MULTIPLAYER_HPP_INCLUDED
