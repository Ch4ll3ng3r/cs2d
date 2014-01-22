#ifndef PAUSE_HPP_INCLUDED
#define PAUSE_HPP_INCLUDED

#include "GameState.hpp"

class CPause : public CGameState
{
    public:
        CPause (sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType);
        void SetGameStateTypeBeforePause (EGameStateType GameStateTypeBeforePause);
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents ();
        void ProcessMouseEvents ();
        void Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts);

    private:
        EGameStateType m_GameStateTypeBeforePause;
};

#endif // PAUSE_HPP_INCLUDED*/
