#ifndef MULTIPLAYER_HPP_INCLUDED
#define MULTIPLAYER_HPP_INCLUDED

#include "GameState.hpp"
#include "Collision.hpp"
#include "Movement.hpp"
#include "Shot.hpp"
#include <SFML/Network.hpp>
#include "Bullet.hpp"
#include "BigFuckingGun.hpp"
#include "Shotgun.hpp"
#include "RocketLauncher.hpp"

class CMultiplayer : public CGameState
{
    public:
        CMultiplayer (map<string, sf::Texture> *p_pTextures, sf::RenderWindow *pWindow,
                      EGameStateType *pCurGameStateType, CLogfile *pLogfile);
        ~CMultiplayer ();
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents (unsigned int p_uiElapsed);
        void ProcessMouseEvents (unsigned int p_uiElapsed, unsigned int p_uiNow);
        void ProcessGameEvents ();
        void CheckCollisions ();
        void UpdateView ();
        void Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts);
        void SendPackets (unsigned int uiNow);
        void ReceivePackets (unsigned int uiNow);
        void UpdateBullets (unsigned int p_uiElapsed);
        bool ConnectionEstablished ();

    private:
        CMap *m_pMap;
        CPlayer *m_pPlayerLocal;
        CPlayer *m_pPlayerConnected;
        CWeapon *m_pWeapon;
        vector<CEvent*> m_vpPendingEvents;
        vector<CBullet*> m_vpBullets;
        sf::TcpSocket m_TcpSocket;
        sf::UdpSocket m_UdpSocket;
        sf::IpAddress m_Ip;
        unsigned short m_usLocalPort;
        unsigned short m_usRemotePort;
        bool m_bConnected;
        bool m_bOffline;
};

#endif // MULTIPLAYER_HPP_INCLUDED
