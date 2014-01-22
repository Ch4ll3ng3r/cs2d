#include "../include/GameState.hpp"

CGameState::CGameState (sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType)
{
    m_pWindow = pWindow;
    m_pCurGameStateType = pCurGameStateType;
}

CGameState::~CGameState ()
{
    // sprites
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        SAFE_DELETE (*i);
    }

    // texts
    vector<sf::Text*>::iterator j;
    for (j = m_vpTexts.begin (); j < m_vpTexts.end (); j++)
    {
        SAFE_DELETE (*j);
    }
}

void CGameState::FillSpriteList (vector<sf::Sprite*> *vpSprites)
{
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        vpSprites->push_back (*i);
    }
}

void CGameState::FillTextList (vector<sf::Text*> *vpTexts)
{
    vector<sf::Text*>::iterator i;
    for (i = m_vpTexts.begin (); i < m_vpTexts.end (); i++)
    {
        vpTexts->push_back (*i);
    }
}
