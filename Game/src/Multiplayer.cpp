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
    m_pMap = new CMap (&m_vpSprites);
    if (m_pMap->Load ("test"))
    {
        cout << "map successfully loaded" << endl;
        m_pMap->UpdateBlockTextures (pTextures);
    }
    else
        cout << "failed to load map";

    // init player
    sf::Sprite *pSprite = nullptr;
    pSprite = new sf::Sprite (pTextures->at ("Player"));
    m_vpSprites.push_back (pSprite);
    sf::Vector2f fViewSize;
    fViewSize.x = static_cast<float> (m_pWindow->getSize ().x);
    fViewSize.y = static_cast<float> (m_pWindow->getSize ().y);
    m_pPlayer = new CPlayer (pSprite, m_pMap->GetTSpawnPos (), fViewSize);
    pSprite = nullptr;
}

CMultiplayer::~CMultiplayer ()
{
    vector<CEvent*>::iterator i;
    for (i = m_vpPendingEvents.begin (); i < m_vpPendingEvents.end (); i++)
    {
        SAFE_DELETE (*i);
    }
    SAFE_DELETE (m_pMap);
    SAFE_DELETE (m_pPlayer);
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
    m_pPlayer->DecreaseVelocity (uiElapsed);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::W))
    {
        m_pPlayer->SetMovementDirection (0.f);
        m_pPlayer->IncreaseVelocity (uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::S))
    {
        m_pPlayer->SetMovementDirection (180.f);
        m_pPlayer->IncreaseVelocity (uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::D))
    {
        m_pPlayer->SetMovementDirection (90.f);
        m_pPlayer->IncreaseVelocity (uiElapsed);
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::A))
    {
        m_pPlayer->SetMovementDirection (270.f);
        m_pPlayer->IncreaseVelocity (uiElapsed);
    }

    /*if (m_pPlayer->GetCurVelocity () > 0.f)
    {
        CMovement *pMovement = nullptr;
        pMovement = new CMovement (m_pPlayer);
        m_vpPendingEvents.push_back (pMovement);
        pMovement = nullptr;
    }*/
}

void CMultiplayer::ProcessMouseEvents (unsigned int uiElapsed)
{
    if (sf::Mouse::getPosition (*m_pWindow).x != 960)
    {
        m_pPlayer->Rotate (static_cast<float> (sf::Mouse::getPosition (*m_pWindow).x - 960), uiElapsed);
        /*if (m_pPlayer->GetCurVelocity () == 0.f)
        {
            CMovement *pMovement = nullptr;
            pMovement = new CMovement (m_pPlayer);
            m_vpPendingEvents.push_back (pMovement);
            pMovement = nullptr;
        }*/
    }
    sf::Mouse::setPosition (sf::Vector2i (960, 540), *m_pWindow);
}

void CMultiplayer::CheckCollisions ()
{
    // collision check
    bool bCollided = false;
    for (int i = 0; i < 100 /*|| bCollided*/; i++)
    {
        for (int j = 0; j < 100 /*|| bCollided*/; j++)
        {
            if (m_pMap->GetBlock (i, j)->IsStable ())
            {
                sf::Vector2f fPos = m_pPlayer->GetPos ();
                float fDirection = m_pPlayer->GetView ().getRotation ();
                fDirection -= 90.f;
                fPos.x += 30.f * cos (DEG_TO_RAD(fDirection));
                fPos.y += 30.f * sin (DEG_TO_RAD(fDirection));
                fDirection += 90.f;
                fPos.x += 30.f * cos (DEG_TO_RAD(fDirection));
                fPos.y += 30.f * sin (DEG_TO_RAD(fDirection));

                for (int k = 0; k < 4; k++)
                {
                    fDirection += 90.f;
                    fPos.x += 60.f * cos (DEG_TO_RAD(fDirection));
                    fPos.y += 60.f * sin (DEG_TO_RAD(fDirection));
                    if (m_pMap->GetBlock (i, j)->CheckCollision (fPos))
                        bCollided = true;
                }
            }
        }
    }

    // consequences
    if (bCollided)
    {
        CCollision *pCollision = nullptr;
        pCollision = new CCollision (m_pPlayer);
        m_vpPendingEvents.push_back (pCollision);
        pCollision = nullptr;
    }
    CMovement *pMovement = nullptr;
    pMovement = new CMovement (m_pPlayer);
    m_vpPendingEvents.push_back (pMovement);
    pMovement = nullptr;
}

void CMultiplayer::UpdateView ()
{
    m_pWindow->setView (m_pPlayer->GetView ());
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
