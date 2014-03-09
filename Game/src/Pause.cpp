#include "../include/Pause.hpp"

CPause::CPause (sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType, CLogfile *pLogfile)
: CGameState (pWindow, pCurGameStateType, pLogfile)
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

void CPause::ProcessKeyboardEvents (unsigned int p_uiElapsed)
{
    // nothing
}

void CPause::ProcessMouseEvents (unsigned int p_uiElapsed, unsigned int p_uiNow)
{
    // nothing
}
