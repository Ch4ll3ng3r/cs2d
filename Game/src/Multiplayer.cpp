#include "../include/Multiplayer.hpp"

CMultiplayer::CMultiplayer (map<string, sf::Texture> *pTextures, sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType)
: CGameState (pWindow, pCurGameStateType)
{
    // block sprites
    for (int i = 0; i < 10000; i++)
    {
        sf::Sprite *pSprite = nullptr;
        pSprite = new sf::Sprite (pTextures->at ("block_error"));
        m_vpSprites.push_back (pSprite);
        pSprite = nullptr;
    }

    // init map
    m_pMap = nullptr;
    m_pMap = new CMap (&m_vpSprites);
    if (m_pMap->Load ("test"))
    {
        cout << "map successfully loaded" << endl;
        m_pMap->UpdateBlockTextures (pTextures);
    }
    else
        cout << "[ERROR] failed to load map";

    // init player
    sf::Sprite *pSprite = nullptr;
    pSprite = new sf::Sprite (pTextures->at ("Player"));
    m_vpSprites.push_back (pSprite);
    sf::Vector2f fViewSize;
    fViewSize.x = static_cast<float> (m_pWindow->getSize ().x);
    fViewSize.y = static_cast<float> (m_pWindow->getSize ().y);
    m_pPlayerLocal = new CPlayer (pSprite, m_pMap->GetTSpawnPos (), fViewSize);
    pSprite = nullptr;
    pSprite = new sf::Sprite (pTextures->at ("Player"));
    m_vpSprites.push_back (pSprite);
    m_pPlayerConnected = new CPlayer (pSprite, m_pMap->GetTSpawnPos (), fViewSize);
    pSprite = nullptr;

    // connect to server
    cout << "ip: ";
    cin >> m_Ip;
    m_usRemotePort = 53000;
    m_usLocalPort = m_usRemotePort + 1;
    if (m_TcpSocket.connect (m_Ip, m_usRemotePort, sf::seconds (1)) == sf::Socket::Done)
    {
        cout << "connection to " << m_Ip << " established" << endl;
        m_TcpSocket.setBlocking (false);
        if (m_UdpSocket.bind (m_usLocalPort) == sf::Socket::Done)
        {
            m_UdpSocket.setBlocking (false);
            m_bConnected = true;
            cout << "bound UdpSocket on port " << m_usLocalPort << endl;
        }
        else
        {
            m_bConnected = false;
            cout << "[ERROR] failed to bind UdpSocket on port " << m_usLocalPort << endl;
        }
    }
    else
    {
        m_bConnected = false;
        cout << "[ERROR] failed to connect to " << m_Ip << endl;
    }
}

CMultiplayer::~CMultiplayer ()
{
    vector<CEvent*>::iterator i;
    for (i = m_vpPendingEvents.begin (); i < m_vpPendingEvents.end (); i++)
    {
        SAFE_DELETE (*i);
    }
    SAFE_DELETE (m_pMap);
    SAFE_DELETE (m_pPlayerLocal);
    SAFE_DELETE (m_pPlayerConnected);
}

void CMultiplayer::ProcessWindowEvents ()
{
    sf::Event event;
    while (m_pWindow->pollEvent(event))
    {
        switch (event.type)
        {
            // window close
            case sf::Event::Closed:
            {
                m_pWindow->close ();
                *m_pCurGameStateType = EXIT;
            } break;

            // keyboard pressed
            case sf::Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    // close window
                    case sf::Keyboard::Escape:
                    {
                        *m_pCurGameStateType = MENU;
                    } break;

                    // default
                    default:
                    {
                        // nothing
                    }
                }
            } break;

            // default
            default:
            {
                // nothing
            }
        }
    }
}

void CMultiplayer::ProcessKeyboardEvents (unsigned int uiElapsed)
{
    m_pPlayerLocal->DecreaseVelocity (uiElapsed);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::E))
    {
        m_pPlayerLocal->SetMovementDirection (0.f);
        m_pPlayerLocal->IncreaseVelocity (uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::D))
    {
        m_pPlayerLocal->SetMovementDirection (180.f);
        m_pPlayerLocal->IncreaseVelocity (uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::F))
    {
        m_pPlayerLocal->SetMovementDirection (90.f);
        m_pPlayerLocal->IncreaseVelocity (uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::S))
    {
        m_pPlayerLocal->SetMovementDirection (270.f);
        m_pPlayerLocal->IncreaseVelocity (uiElapsed);
    }
}

void CMultiplayer::ProcessMouseEvents (unsigned int uiElapsed)
{
    if (sf::Mouse::getPosition (*m_pWindow).x != 960)
        m_pPlayerLocal->Rotate (static_cast<float> (sf::Mouse::getPosition (*m_pWindow).x - 960), uiElapsed);
    sf::Mouse::setPosition (sf::Vector2i (960, 540), *m_pWindow);
}

void CMultiplayer::CheckCollisions (unsigned int uiElapsed)
{
    // collision check
    if (m_pPlayerLocal->RequestsMovement ())
    {
        m_pPlayerLocal->Move (uiElapsed);
        bool bCollided = false;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (m_pMap->GetBlock (i, j)->IsStable ())
                {
                    sf::Vector2f fPos = m_pPlayerLocal->GetPos ();
                    float fDirection = m_pPlayerLocal->GetViewDirection ();
                    fDirection -= 90.f;
                    fPos.x += 30.f * cos (DEG_TO_RAD(fDirection));
                    fPos.y += 30.f * sin (DEG_TO_RAD(fDirection));
                    fDirection += 90.f;
                    fPos.x += 30.f * cos (DEG_TO_RAD(fDirection));
                    fPos.y += 30.f * sin (DEG_TO_RAD(fDirection));

                    for (int k = 0; k < 4; k++)
                    {
                        fDirection += 90.f;
                        for (int l = 0; l < 60; l++)
                        {
                            fPos.x += 1.f * cos (DEG_TO_RAD(fDirection));
                            fPos.y += 1.f * sin (DEG_TO_RAD(fDirection));
                            if (m_pMap->GetBlock (i, j)->CheckCollision (fPos))
                                bCollided = true;
                        }
                    }
                }
            }
        }

        // consequences
        if (bCollided)
        {
            CCollision *pCollision = nullptr;
            pCollision = new CCollision (m_pPlayerLocal);
            m_vpPendingEvents.push_back (pCollision);
            pCollision = nullptr;
        }
        else
        {
            CMovement *pMovement = nullptr;
            pMovement = new CMovement (m_pPlayerLocal);
            m_vpPendingEvents.push_back (pMovement);
            pMovement = nullptr;
        }
    }
}

void CMultiplayer::UpdateView ()
{
    m_pWindow->setView (m_pPlayerLocal->GetView ());
}

void CMultiplayer::Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts)
{
    FillSpriteList (vpSprites);
    m_pWindow->setMouseCursorVisible (false);
}

void CMultiplayer::ProcessGameEvents ()
{
    vector<CEvent*>::iterator i;
    for (i = m_vpPendingEvents.begin (); i < m_vpPendingEvents.end (); i++)
    {
        (*i)->Handle ();
        SAFE_DELETE (*i);
    }
    m_vpPendingEvents.clear ();
}

void CMultiplayer::SendPackets (unsigned int uiNow)
{
    sf::Packet packet;
    packet << m_pPlayerLocal->GetPos ().x << m_pPlayerLocal->GetPos ().y << m_pPlayerLocal->GetViewDirection ();
    if (m_TcpSocket.send (packet) == sf::Socket::Done) {}
    /*packet << PING << uiNow;
    if (m_TcpSocket.send (packet) != sf::Socket::Done) {}*/
}

void CMultiplayer::ReceivePackets (unsigned int uiNow)
{
    sf::Packet packet;
    sf::Vector2f fPos;
    float fDirection = 0.f;
    if (m_TcpSocket.receive (packet) == sf::Socket::Done)
    {
        if (packet >> fPos.x >> fPos.y >> fDirection)
        {
            m_pPlayerConnected->SetViewDirection (fDirection);
            m_pPlayerConnected->SetPos (fPos);
        }
    }
    /*if (m_TcpSocket.receive (packet) == sf::Socket::Done)
    {
        if (packet >> m_CurPacketType)
        {
            switch (m_CurPacketType)
            {
                case PING:
                {
                    unsigned int uiPacketSendTime = 0;
                    if (packet >> uiPacketSendTime)
                        cout << "ping: " << uiNow - uiPacketSendTime << endl;
                } break;
                case SHUTDOWN:
                {
                    m_bConnected = false;
                } break;
                default: {}
            }
        }
    }*/
}

bool CMultiplayer::ConnectionEstablished ()
{
    return m_bConnected;
}
