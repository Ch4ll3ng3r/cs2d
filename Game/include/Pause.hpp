#ifndef PAUSE_HPP_INCLUDED
#define PAUSE_HPP_INCLUDED

#include "GameState.hpp"

class CPause : public CGameState
{
    public:
        CPause (sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType, CLogfile *pLogfile);
        void SetGameStateTypeBeforePause (EGameStateType GameStateTypeBeforePause);
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents (unsigned int p_uiElapsed);
        void ProcessMouseEvents (unsigned int p_uiElapsed, unsigned int p_uiNow);
        void Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts);

    private:
        EGameStateType m_GameStateTypeBeforePause;
};

#endif // PAUSE_HPP_INCLUDED*/
