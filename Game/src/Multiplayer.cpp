#include "../include/Multiplayer.hpp"

CMultiplayer::CMultiplayer (map<string, sf::Texture> *p_pTextures, sf::RenderWindow *pWindow,
                            EGameStateType *pCurGameStateType, CLogfile *pLogfile)
: CGameState (pWindow, pCurGameStateType, pLogfile)
{
    // init weapons
    m_pWeapon = nullptr;
    m_pWeapon = new CRocketLauncher (&p_pTextures->at ("BulletRocketLauncher"));

    // block sprites
    for (int i = 0; i < 10000; i++)
    {
        sf::Sprite *pSprite = nullptr;
        pSprite = new sf::Sprite (p_pTextures->at ("block_error"));
        m_vpSprites.push_back (pSprite);
        pSprite = nullptr;
    }

    // init map
    m_pMap = nullptr;
    m_pMap = new CMap (&m_vpSprites);
    if (m_pMap->Load ("test"))
    {
        m_pLogfile->Write ("map loaded");
        m_pMap->UpdateBlockTextures (p_pTextures);
    }
    else
    {
        cout << "[ERROR] failed to load map";
        m_pLogfile->Write ("[ERROR] failed to load map");
    }

    // init player
    sf::Sprite *pSprite = nullptr;
    pSprite = new sf::Sprite (p_pTextures->at ("Player"));
    m_vpSprites.push_back (pSprite);
    sf::Vector2f fViewSize;
    fViewSize.x = static_cast<float> (m_pWindow->getSize ().x);
    fViewSize.y = static_cast<float> (m_pWindow->getSize ().y);
    m_pPlayerLocal = new CPlayer (pSprite, m_pMap->GetTSpawnPos (), fViewSize, m_pWeapon);
    pSprite = nullptr;
    pSprite = new sf::Sprite (p_pTextures->at ("Player"));
    m_vpSprites.push_back (pSprite);
    m_pPlayerConnected = new CPlayer (pSprite, m_pMap->GetTSpawnPos (), fViewSize, nullptr);
    pSprite = nullptr;

    // connect to server
    cout << "ip: ";
    cin >> m_Ip;
    if (m_Ip == "0.0.0.0")
    {
        m_bOffline = true;
        m_bConnected = false;
        cout << "starting in offline mode" << endl;
        m_pLogfile->Write ("starting in offline mode");
    }
    else
        m_bOffline = false;
    if (!m_bOffline)
    {
        m_usRemotePort = 53000;
        m_usLocalPort = m_TcpSocket.getLocalPort ();
        if (m_TcpSocket.connect (m_Ip, m_usRemotePort, sf::seconds (1)) == sf::Socket::Done)
        {
            cout << "connection to " << m_Ip << " established" << endl;
            m_pLogfile->Write ("connection to " + m_Ip.toString () + "established");
            m_TcpSocket.setBlocking (false);
            m_bConnected = true;
        }
        else
        {
            m_bConnected = false;
            cout << "[ERROR] failed to connect to " << m_Ip << endl;
            m_pLogfile->Write ("[ERROR] failed to connect to " + m_Ip.toString ());
        }
    }
    p_pTextures = nullptr;
}

CMultiplayer::~CMultiplayer ()
{
    vector<CEvent*>::iterator i;
    for (i = m_vpPendingEvents.begin (); i < m_vpPendingEvents.end (); i++)
    {
        SAFE_DELETE (*i);
    }
    vector<CBullet*>::iterator j;
    for (j = m_vpBullets.begin (); j < m_vpBullets.end (); j++)
    {
        SAFE_DELETE (*j);
    }
    SAFE_DELETE (m_pMap);
    SAFE_DELETE (m_pPlayerLocal);
    SAFE_DELETE (m_pPlayerConnected);;
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

void CMultiplayer::ProcessKeyboardEvents (unsigned int p_uiElapsed)
{
    m_pPlayerLocal->DecreaseVelocity (p_uiElapsed);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::E))
    {
        m_pPlayerLocal->SetMovementDirection (0.f);
        m_pPlayerLocal->IncreaseVelocity (p_uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::D))
    {
        m_pPlayerLocal->SetMovementDirection (180.f);
        m_pPlayerLocal->IncreaseVelocity (p_uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::F))
    {
        m_pPlayerLocal->SetMovementDirection (90.f);
        m_pPlayerLocal->IncreaseVelocity (p_uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::S))
    {
        m_pPlayerLocal->SetMovementDirection (270.f);
        m_pPlayerLocal->IncreaseVelocity (p_uiElapsed);
    }
}

void CMultiplayer::ProcessMouseEvents (unsigned int p_uiElapsed, unsigned int p_uiNow)
{
    // rotating
    if (sf::Mouse::getPosition (*m_pWindow).x != 960)
        m_pPlayerLocal->Rotate (static_cast<float> (sf::Mouse::getPosition (*m_pWindow).x - 960), p_uiElapsed);
    sf::Mouse::setPosition (sf::Vector2i (960, 540), *m_pWindow);

    // shooting
    if (sf::Mouse::isButtonPressed (sf::Mouse::Left))
    {
        CShot *pShot = nullptr;
        pShot = new CShot (m_pPlayerLocal, p_uiNow, &m_vpSprites, &m_vpBullets);
        m_vpPendingEvents.push_back (pShot);
        pShot = nullptr;
    }
}

void CMultiplayer::CheckCollisions ()
{
    // collision check
    if (m_pPlayerLocal->RequestsMovement ())
    {
        m_pPlayerLocal->Move ();
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
    if (m_TcpSocket.send (packet) != sf::Socket::Done) {}
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

void CMultiplayer::UpdateBullets (unsigned int p_uiElapsed)
{
    for (vector<CBullet*>::iterator i = m_vpBullets.begin (); i != m_vpBullets.end (); i++)
    {
        (*i)->Fly (p_uiElapsed);
    }
}

void CMultiplayer::UpdateSpriteList (vector<sf::Sprite*> *p_vpSprites)
{
    for (unsigned int i = p_vpSprites->size (); i < m_vpSprites.size (); i++)
    {
        p_vpSprites->push_back (m_vpSprites.at (i));
    }

}
