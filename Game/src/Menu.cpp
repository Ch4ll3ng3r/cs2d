#include "../include/Menu.hpp"

CMenu::CMenu (map<string, sf::Texture> *pTextures, map<string, sf::Font> *pFonts,
               sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType)
: CGameState (pWindow, pCurGameStateType)
{
    m_pButtonExit = nullptr;
    m_pButtonPlay = nullptr;
    sf::Sprite *pSprite = nullptr;
    pSprite = new sf::Sprite (pTextures->at ("MenuBackground"));
    m_vpSprites.push_back (pSprite);
    pSprite = nullptr;
    pSprite = new sf::Sprite (pTextures->at ("Button"));
    m_vpSprites.push_back (pSprite);
    sf::Vector2f fButtonPos = sf::Vector2f (200.f, 200.f);
    sf::Vector2i iButtonSize = sf::Vector2i (250, 100);
    sf::Text *pText = nullptr;
    pText = new sf::Text ("pimmel", pFonts->at ("arial"), 30);
    m_vpTexts.push_back (pText);
    m_pButtonPlay = new CButton (fButtonPos, iButtonSize, pSprite, pText, "PLAY");
    pSprite = nullptr;
    pSprite = new sf::Sprite (pTextures->at ("Button"));
    m_vpSprites.push_back (pSprite);
    fButtonPos = sf::Vector2f (200.f, 400.f);
    //iButtonSize = sf::Vector2i (250, 100);
    pText = nullptr;
    pText = new sf::Text ("pimmel", pFonts->at ("arial"), 30);
    m_vpTexts.push_back (pText);
    m_pButtonExit = new CButton (fButtonPos, iButtonSize, pSprite, pText, "EXIT");
    pSprite = nullptr;
    pText = nullptr;
}

CMenu::~CMenu ()
{
    SAFE_DELETE (m_pButtonPlay);
    SAFE_DELETE (m_pButtonExit);
}

void CMenu::ProcessWindowEvents ()
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
                        m_pWindow->close ();
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

void CMenu::ProcessKeyboardEvents ()
{

}

void CMenu::ProcessMouseEvents ()
{
    if (sf::Mouse::isButtonPressed (sf::Mouse::Button::Left))
    {
        sf::Vector2f fMousePos = sf::Vector2f (static_cast<float> (sf::Mouse::getPosition ().x),
                                               static_cast<float> (sf::Mouse::getPosition ().y));
        if (m_pButtonExit->CheckCollision (fMousePos))
            *m_pCurGameStateType = EXIT;
        else if (m_pButtonPlay->CheckCollision (fMousePos))
            *m_pCurGameStateType = MULTIPLAYER;
    }
}

void CMenu::Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts)
{
    FillSpriteList (vpSprites);
    FillTextList (vpTexts);
    m_pWindow->setMouseCursorVisible (true);
}
