#include "../include/Pause.hpp"

CPause::CPause (sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType)
: CGameState (pWindow, pCurGameStateType)
{
    // nothing
}

void CPause::SetGameStateTypeBeforePause (EGameStateType GameStateTypeBeforePause)
{
    m_GameStateTypeBeforePause = GameStateTypeBeforePause;
}

void CPause::ProcessWindowEvents ()
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

            // window gained focus
            case sf::Event::GainedFocus:
            {
                *m_pCurGameStateType = m_GameStateTypeBeforePause;
            } break;

            // default
            default:
            {
                // nothing
            }
        }
    }
}

void CPause::Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts)
{
    // nothing
}

void CPause::ProcessKeyboardEvents ()
{
    // nothing
}

void CPause::ProcessMouseEvents ()
{
    // nothing
}
